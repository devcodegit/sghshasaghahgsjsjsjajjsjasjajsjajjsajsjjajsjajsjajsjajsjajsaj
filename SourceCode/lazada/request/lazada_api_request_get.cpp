#include "lazada_api_request_get.h"
#include "../lazada_define.h"
#include "../../core/utils/coredefine.h"
#include "../../core/jsonutil/json_utils.h"
#include "../../core/jsonutil/json_exception.h"
#include "../../core/dataitem/abstract_data_item.h"

#include <QMessageAuthenticationCode>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>

using namespace Core::DataItem;
using namespace Core::Request;
using namespace Core::Json;
using namespace Core::ErrorCode;

const QString SIGNKEY_PREFIX = "Signature";

LazadaApiRequestGET::LazadaApiRequestGET()
{

}

QString LazadaApiRequestGET::generateSignature(QString data, QString key)
{
    if (data.isEmpty() || key.isEmpty()) return "";
    return QMessageAuthenticationCode::hash(data.toUtf8(), key.toUtf8(), QCryptographicHash::Sha256).toHex();
}

QString LazadaApiRequestGET::prepareGETParams(QHash<QString, QString> *a_pParams)
{
    QString strParams = "";
    QStringList listKeys = QStringList(a_pParams->keys());

    if (listKeys.count() > 0)
    {
        listKeys.sort();

        for (int i = 0; i < listKeys.count(); ++i)
        {
            QString i_sKey = listKeys.at(i);
            QString i_sValue = a_pParams->value(i_sKey, "");
            strParams += i_sKey + "=" + QUrl::toPercentEncoding(i_sValue);
            if (i < listKeys.length() - 1)
            {
                strParams += "&";
            }
        }

        QString i_qsSignature = generateSignature(strParams, KEY_LAZADA_USER);
        // Add signature to params list
        strParams += "&" + SIGNKEY_PREFIX + "=" + i_qsSignature;
    }

    return strParams;
}

void LazadaApiRequestGET::parseData(const QByteArray &a_ResponseData)
{
    qDebug() << "vao ne";
    m_iErrorCode = CoreErrorCode::ERROR_NONE;
    QString i_sResponseString = QString::fromUtf8(a_ResponseData);
    qDebug() << "json = " << i_sResponseString.indexOf("SuccessResponse");

    Document i_ResponseObj;
    if (i_sResponseString.indexOf("SuccessResponse") == 2)
    {
        //parse success
        JsonUtils::parseJson(i_ResponseObj, i_sResponseString);
        ParseDataSuccess(i_ResponseObj);
    }
    else if (i_sResponseString.indexOf("ErrorResponse") == 2)
    {
        //parse error
        JsonUtils::parseJson(i_ResponseObj, i_sResponseString);
        ParseDataError(i_ResponseObj);
    }
}

int LazadaApiRequestGET::parseErrorCode(Value &aJsonObject)
{
    int i_iResponseCode = JsonUtils::getInt(aJsonObject, "ErrorCode");
    // Try parse error message
    m_sErrorMsg = JsonUtils::tryGetString(aJsonObject, "ErrorMessage", "");
    return i_iResponseCode;
}

QString LazadaApiRequestGET::getTimestamp()
{
    QDateTime now = QDateTime::currentDateTime();
    int offset = now.offsetFromUtc();
    now.setOffsetFromUtc(offset);
    return now.toString(Qt::ISODate);
}

void LazadaApiRequestGET::ParseDataError(Value &aJsonObject)
{
    m_iErrorCode = JsonUtils::tryGetInt(aJsonObject, "ErrorCode", 0);
    m_sErrorMsg = JsonUtils::tryGetString(aJsonObject, "ErrorMessage", "");
    qDebug() << "ParseDataError == " << m_iErrorCode << m_sErrorMsg;
}

void LazadaApiRequestGET::ParseDataSuccess(Value &aJsonObject)
{
    qDebug() << "ParseDataSuccess";
    try
    {
        if (!aJsonObject.IsNull())
        {
            Value &objSuccess = JsonUtils::getJsonObject(aJsonObject, "SuccessResponse");
            if (!objSuccess.IsNull())
            {
                qDebug() << "parse Success";

                Value &objHead = JsonUtils::getJsonObject(objSuccess, "Head");
                ParseHead(objHead);

                Value &objBody = JsonUtils::getJsonObject(objSuccess, "Body");
                ParseBody(objBody);
            }
            else
            {
                qDebug() << "Parse Error";
                m_iErrorCode = CoreErrorCode::ERROR_PARSE_JSON;
            }
        }
    }
    catch (JsonException ex)
    {
        m_iErrorCode = CoreErrorCode::ERROR_PARSE_JSON;
        qDebug() << "Error = " << ex.what();
    }
}

void LazadaApiRequestGET::ParseHead(Value &aJsonObject)
{
    qDebug() << "LazadaApiRequestGET::ParseHead";
    if (!aJsonObject.IsNull())
    {
        try
        {
            _strRequestId = JsonUtils::tryGetString(aJsonObject, "RequestId", "");
            _strRequestAction = JsonUtils::tryGetString(aJsonObject, "RequestAction", "");
            _strResponseType = JsonUtils::tryGetString(aJsonObject, "ResponseType", "");
            _strTimeStamp = JsonUtils::tryGetString(aJsonObject, "Timestamp", "");
            _iTotalCount = JsonUtils::tryGetInt(aJsonObject, "TotalCount", 0);
            qDebug() << "Head: " << _strRequestId << _strRequestAction << _strResponseType << _iTotalCount;
        }
        catch (JsonException ex)
        {
            qDebug() << "Parse Json Fail: " << ex.what();
            m_iErrorCode = CoreErrorCode::ERROR_PARSE_JSON;
        }
    }
    else
    {
        m_iErrorCode = CoreErrorCode::ERROR_PARSE_JSON;
    }
}

void LazadaApiRequestGET::ParseBody(Value &aJsonObject)
{
    qDebug() << "LazadaApiRequestGET::ParseBody";
    if (!aJsonObject.IsNull())
    {
        if (m_pDataItem)
        {
            m_pDataItem->parseItemData(aJsonObject);
        }
    }
    else
    {
        m_iErrorCode = CoreErrorCode::ERROR_PARSE_JSON;
    }

}
