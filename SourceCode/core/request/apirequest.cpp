#include "apirequest.h"
#include "request_utils.h"
#include "../network/sessionmanager.h"
#include "../utils/coredefine.h"
#include "../jsonutil/json_utils.h"

#include <QThread>
#include <QNetworkCookie>

using namespace Core::ErrorCode;
using namespace Core::Request;
using namespace Core::Network;
using namespace Core::Json;

ApiRequest::ApiRequest() :
    m_ePriority(RequestPriority::NORMAL),
    m_iRequestId(RequestUtils::GET_REQUEST_ID()),
    m_iErrorCode(CoreErrorCode::ERROR_NONE),
    m_iRequestType(-1),
    m_iTimeoutRequest(-1),
    m_pDataItem(NULL),
    m_pApiRequestListener(NULL),
    m_pHttpConnection(NULL),
    m_pWorkerThread(NULL)
{
    // connect event and moveToThread if worker thread exits
    m_pWorkerThread = new QThread();
    // Auto stop Thread when Api Destroyed
    connect(this, SIGNAL(destroyed(QObject*)), m_pWorkerThread, SLOT(quit()));
    // Auto Destroyed Thread when Thread itself finish (quit)
    connect(m_pWorkerThread, SIGNAL(finished()), m_pWorkerThread, SLOT(deleteLater()));
    // Move Request to Request Thread to run in separator Thread
    this->moveToThread(m_pWorkerThread);
}

ApiRequest::~ApiRequest()
{
    if (m_pHttpConnection)
    {
        m_pHttpConnection->deleteLater();
        m_pHttpConnection = NULL;
    }
    if (m_pDataItem)
    {
        delete m_pDataItem;
        m_pDataItem = NULL;
    }
}

void ApiRequest::setParser(AbstractDataItem *parser)
{
    m_pDataItem = parser;
}

void ApiRequest::setFinishListener(IApiFinishListener *aListener)
{
    m_pFinishListener = aListener;
}

void ApiRequest::Handle(QNetworkAccessManager *a_pNetworkManager)
{
    if (!m_pHttpConnection)
    {
        m_pHttpConnection = new HttpConnection();
        connect(m_pHttpConnection, SIGNAL(notifyRequestComplete()), this, SLOT(onHttpConnectionComplete()));
    }

    QString urlRequest = "";

    if (m_eRequestMethod == RequestMethod::GET)
    {
        // Get List param
        QHash<QString, QString> i_Params;
        generateParams(&i_Params);

        // Build request param string from list Params
        QString strParams = prepareGETParams(&i_Params);

        if (!strParams.isEmpty())
        {
            urlRequest = m_sDomainUrl + "?" + strParams;
            qDebug() << "Url request == " << urlRequest;
            m_pHttpConnection->openGetConnection(a_pNetworkManager, urlRequest, QList<QNetworkCookie>(), m_iTimeoutRequest);
        }
    }
    else if (m_eRequestMethod == RequestMethod::POST)
    {

    }
}

void ApiRequest::Start()
{
    if (m_pWorkerThread != nullptr)
    {
        m_pWorkerThread->start();
    }
}

ApiRequest::RequestPriority ApiRequest::getPriority()
{
    return m_ePriority;
}

void ApiRequest::cancelRequest()
{
    if (m_pHttpConnection)
    {
        m_pHttpConnection->Cancel();
    }
}

int ApiRequest::getRequestId()
{
    return m_iRequestId;
}

int ApiRequest::getErrorCode()
{
    return m_iErrorCode;
}

QString ApiRequest::getErrorMessage()
{
    return m_sErrorMsg;
}

int ApiRequest::getRequestType()
{
    return m_iRequestType;
}

AbstractDataItem *ApiRequest::getDataItem()
{
    return m_pDataItem;
}

void ApiRequest::onHttpConnectionComplete()
{
    qDebug() << "onHttpConnectionComplete";
    // Notify to Worker Thread to Remove current Request
    // Notify soon to give slot to next request
    if (m_pFinishListener)
    {
        m_pFinishListener->OnApiFinish(this->getRequestId());
    }

    // This slot run in ApiRequest Thread (this thread)
    m_iErrorCode = m_pHttpConnection->getResponseCode();
    if (m_iErrorCode == CoreErrorCode::ERROR_NONE)
    {
        qDebug() << "parse success data";
        // Parse Response Data
        parseData(m_pHttpConnection->getResponseData());
    }

    // Log
    // Callback to ApiRequestListener to handle value
    if (m_iErrorCode == CoreErrorCode::ERROR_NONE)
    {
        if (m_pApiRequestListener)
        {
            m_pApiRequestListener->OnApiRequestComplete(this);
        }
    }
    else
    {
       qDebug() << "ApiRequest Error: " <<  m_iRequestId << m_iRequestType << m_iErrorCode;
        if (m_pApiRequestListener != nullptr)
        {
            m_pApiRequestListener->OnApiRequestError(this);
        }
    }

    if(m_isAutoDelete) {
        // Self delete
        this->deleteLater();
    }

    DoCompletedApiRequest();
}
