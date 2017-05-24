#include "http_connection.h"
#include "network_session_manager.h"
#include "network_manager_factory.h"
#include "../utils/coredefine.h"
#include "../utils/gzip_utils.h"

#include <QNetworkCookie>

using namespace Core::Network;
using namespace Core::ErrorCode;
using namespace Core::Utility;

static const QString CONTENT_ENCODING_HEADER = "Content-Encoding";
static const QString ACCEPT_ENCODING_HEADER = "Accept-Encoding";
static const QString ACCEPT_ENCODING_VALUE = "gzip";
static const QString USER_AGENT_HEADER = "User-Agent";
static const QString USER_AGENT_VALUE = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36";
static const QString CONTENT_TYPE_HEADER = "Content-Type";
static const QString CONTENT_TYPE_VALUE = "application/x-www-form-urlencoded";

HttpConnection::HttpConnection()
    : m_pRequestReply(nullptr)
    , m_Lock(QMutex::Recursive) // Enable Recursive because QNetworkReply::abort() call direct to finish signal
    , m_ResponseCode(CoreErrorCode::ERROR_UNKNOW)
{
    m_TimeOutTimer.setSingleShot(true);
    connect(&m_TimeOutTimer, SIGNAL(timeout()), this, SLOT(onRequestTimeout()));
}

HttpConnection::~HttpConnection()
{
    if (m_pRequestReply)
    {
        m_pRequestReply->deleteLater();
        m_pRequestReply = NULL;
    }
    // Stop Timer
    stopTimeoutTimer();
}

void HttpConnection::openGetConnection(QNetworkAccessManager *m_pNetworkManager, const QString &a_sUrl, const QList<QNetworkCookie> &a_CookieList, int a_MilisecTimeOut)
{
    // Check No Network
    if (!NetworkSessionManager::NETWORK_AVAILABE())
    {
        m_ResponseCode = CoreErrorCode::ERROR_NETWORK_NOT_AVAILABE;
        // signal only run when this function finish
        emit notifyRequestComplete();
        return;
    }

    QNetworkAccessManager* i_pNetworkManager;
    if (!m_pNetworkManager)
    {
        // Support new instance of manager if input empty
        // Put parent to this to delete when HttpConnection delete
        i_pNetworkManager = new QNetworkAccessManager(this);
        NetworkManagerFactory::instance()->doConfig(i_pNetworkManager);
    }
    else
    {
        i_pNetworkManager = m_pNetworkManager;
    }

    // Create Url & encode
    QUrl iUrl = QUrl::fromUserInput(a_sUrl);
    // Create Request
    QNetworkRequest iRequest(iUrl);
    // set header
    iRequest.setRawHeader(ACCEPT_ENCODING_HEADER.toUtf8(), ACCEPT_ENCODING_VALUE.toUtf8());
    iRequest.setRawHeader(USER_AGENT_HEADER.toUtf8(), USER_AGENT_VALUE.toUtf8());
    iRequest.setRawHeader(CONTENT_TYPE_HEADER.toUtf8(), CONTENT_TYPE_VALUE.toUtf8());
    // Add Cookie
    for (int iter = 0; iter < a_CookieList.count(); ++iter)
    {
        iRequest.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(a_CookieList[iter]));
    }
    // Content-Length ??

    QMutexLocker iLocker(&m_Lock);
    m_pRequestReply = i_pNetworkManager->get(iRequest);
    connect(m_pRequestReply, SIGNAL(finished()), this, SLOT(onRequestFinish()));
    iLocker.unlock();

    // Start timeout timer
    if(a_MilisecTimeOut < 1) {
        a_MilisecTimeOut = NetworkSessionManager::GET_TIMEOUT(NetworkSessionManager::TimeOutType::HTTP_TIMEOUT);
    }
    m_TimeOutTimer.start(a_MilisecTimeOut);
    // Request, timer only run when this function finish
}

void HttpConnection::openPostConnection(QNetworkAccessManager *m_pNetworkManager, const QString &a_sUrl, const QByteArray &a_PostData, const QList<QNetworkCookie> &a_CookieList, int a_MilisecTimeOut)
{
    // Check No Network
    if (!NetworkSessionManager::NETWORK_AVAILABE())
    {
        m_ResponseCode = CoreErrorCode::ERROR_NETWORK_NOT_AVAILABE;
        // signal only run when this function finish
        emit notifyRequestComplete();
        return;
    }

    QNetworkAccessManager* i_pNetworkManager;
    if (m_pNetworkManager == nullptr)
    {
        // Support new instance of manager if input empty
        // Put parent to this to delete when HttpConnection delete
        i_pNetworkManager = new QNetworkAccessManager(this);
        NetworkManagerFactory::instance()->doConfig(i_pNetworkManager);
    }
    else
    {
        i_pNetworkManager = m_pNetworkManager;
    }

    // Create Url & encode
    QUrl iUrl = QUrl::fromUserInput(a_sUrl);
    // Create Request
    QNetworkRequest iRequest(iUrl);
    // set header
    iRequest.setRawHeader(ACCEPT_ENCODING_HEADER.toUtf8(), ACCEPT_ENCODING_VALUE.toUtf8());
    iRequest.setRawHeader(USER_AGENT_HEADER.toUtf8(), USER_AGENT_VALUE.toUtf8());
    iRequest.setHeader(QNetworkRequest::ContentTypeHeader, CONTENT_TYPE_VALUE);
    // Add Cookie
    for (int iter = 0; iter < a_CookieList.count(); ++iter)
    {
        iRequest.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(a_CookieList[iter]));
    }

    QMutexLocker iLocker(&m_Lock);
    m_pRequestReply = i_pNetworkManager->post(iRequest, a_PostData);
    connect(m_pRequestReply, SIGNAL(finished()), this, SLOT(onRequestFinish()));
    iLocker.unlock();

    // Start timeout timer
    if(a_MilisecTimeOut < 1) {
        a_MilisecTimeOut = NetworkSessionManager::GET_TIMEOUT(NetworkSessionManager::TimeOutType::HTTP_TIMEOUT);
    }
    m_TimeOutTimer.start(a_MilisecTimeOut);
    // Request, timer only run when this function finish
}

void HttpConnection::Cancel()
{
    QMutexLocker iLocker(&m_Lock);
    // Run in thread which call this function so must be lock
    if (m_pRequestReply)
    {
        m_pRequestReply->abort();
    }
    // Stop Timer
    stopTimeoutTimer();
}

int HttpConnection::getResponseCode()
{
    return m_ResponseCode;
}

QByteArray HttpConnection::getResponseData()
{
    return m_ResponseData;
}

void HttpConnection::onRequestFinish()
{
    // Stop Timer
    stopTimeoutTimer();

    QMutexLocker iLocker(&m_Lock);
    // Run in same thread with onRequestTimeOut
    if (m_pRequestReply)
    {
        if (m_pRequestReply->error() == QNetworkReply::NoError)
        {
            // In case 302 it will goes here too
            QByteArray i_ResponseByte = m_pRequestReply->readAll();
            // Check gzip & unzip
            QByteArray i_ContentEncodingByte = m_pRequestReply->rawHeader(CONTENT_ENCODING_HEADER.toUtf8());
            if (QString(i_ContentEncodingByte) == "gzip")
            {
                // Decompress
                if (GZipUtils::gzipDecompress(i_ResponseByte, m_ResponseData))
                {
                    // Decompress Ok
                    m_ResponseCode = CoreErrorCode::ERROR_NONE;
                }
                else
                {
                    // Decompress Error
                    m_ResponseCode = CoreErrorCode::ERROR_DECOMPRESS_GZIP;
                }
            }
            else
            {
                // Not Gzip, use raw data
                m_ResponseData = i_ResponseByte;
                m_ResponseCode = CoreErrorCode::ERROR_NONE;
            }
        }
        else
        {
            QVariant iErrorCodeValue = m_pRequestReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            if (iErrorCodeValue.isValid())
            {
                // Raw status code from http header
                m_ResponseCode = iErrorCodeValue.toInt();
            }
            else
            {
                // In case cancel we need check cancel by timeout or by manual cancel
                if (m_pRequestReply->error() == QNetworkReply::OperationCanceledError && m_ResponseCode == CoreErrorCode::ERROR_REQUEST_TIME_OUT)
                {
                    // keep Client TimeoutError
                }
                else
                {
                    // Error code in QT form, convert it to negative
                    m_ResponseCode = -(int)m_pRequestReply->error();
                }
            }
        }
        // Dont need to Delete Reply - We will delete it at Destructor
    }
    else
    {
        // WRONG case, it should not go here
        qDebug() << "Wrong case onRequestFinish";
    }

    // Notify Finish
    emit notifyRequestComplete();
}

void HttpConnection::onRequestTimeout()
{
    // Stop Timer
    stopTimeoutTimer();

    QMutexLocker iLocker(&m_Lock);
    // Close Connection - run same thread with onRequestFinish
    // Set Error to TimeOutError, it will be handle in finish slot
    m_ResponseCode = CoreErrorCode::ERROR_REQUEST_TIME_OUT;
    if (m_pRequestReply != nullptr)
    {
        m_pRequestReply->abort();
    }
    else
    {
        // WRONG case, it should not go here
        qDebug() << "Wrong case onRequestTimeout";
    }
}

void HttpConnection::stopTimeoutTimer()
{
    if (m_TimeOutTimer.isActive())
    {
        //disconnect(&m_TimeOutTimer, SIGNAL(timeout()), this, SLOT(onRequestTimeout()));
        m_TimeOutTimer.stop();
    }
}
