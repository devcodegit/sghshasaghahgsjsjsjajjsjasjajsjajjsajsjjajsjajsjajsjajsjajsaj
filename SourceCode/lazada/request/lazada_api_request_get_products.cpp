#include "lazada_api_request_get_products.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestGetProducts::LazadaApiRequestGetProducts(IApiRequestListener *a_pListener,QStringList SkuSellerList,const qint64 CreatedAfter, const qint64 CreatedBefore, const qint64 UpdatedAfter, const qint64 UpdatedBefore, const QString &Search,
                                                         const QString &Filter, const int Limit, const int Option, const int Offset)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;

    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_GET_PRODUCT;
    m_CreatedBefore = CreatedBefore;
    m_CreatedAfter = CreatedAfter;
    m_UpdatedAfter = UpdatedAfter;
    m_UpdatedBefore = UpdatedBefore;
    m_Search = Search;
    m_Filter = Filter;
    m_Offset = Offset;
    m_Option = Option;
    m_SkuSellerList = SkuSellerList;
}

void LazadaApiRequestGetProducts::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_GET_PRODUCT);
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);


    if (m_CreatedAfter > 0)
    {
        a_pParams->insert(QString("CreatedAfter"), convertTimeToStringISO8601(m_CreatedAfter));
    }
    if (m_CreatedBefore > 0)
    {
        a_pParams->insert(QString("CreatedBefore"), convertTimeToStringISO8601(m_CreatedBefore));
    }
    if (m_UpdatedAfter > 0)
    {
        a_pParams->insert(QString("UpdatedAfter"), convertTimeToStringISO8601(m_UpdatedAfter));
    }
    if (m_UpdatedBefore > 0)
    {
        a_pParams->insert(QString("UpdatedBefore"), convertTimeToStringISO8601(m_UpdatedBefore));
    }

    if (!m_Search.isEmpty())
    {
        a_pParams->insert(QString("Search"), m_Search);
    }
    if (!m_Filter.isEmpty())
    {
        a_pParams->insert(QString("Filter"), m_Filter);
    }

    if (m_Limit >= 0)
    {
        a_pParams->insert(QString("Limit"), QString::number(m_Limit));
    }
    if (m_Option >= 0)
    {
        a_pParams->insert(QString("Options"), QString::number(m_Option));
    }
    if (m_Offset >= 0)
    {
        a_pParams->insert(QString("Offset"), QString::number(m_Offset));
    }
    if (!m_SkuSellerList.isEmpty())
    {
//        a_pParams->insert(QString("SkuSellerList"), ) chua biet support
    }
}
