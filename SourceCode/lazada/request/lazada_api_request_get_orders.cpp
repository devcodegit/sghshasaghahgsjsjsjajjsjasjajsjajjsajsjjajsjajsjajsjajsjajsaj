#include "lazada_api_request_get_orders.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestGetOrders::LazadaApiRequestGetOrders(IApiRequestListener *a_pListener, const int Limit, const int Offset, const qint64 CreatedAfter, const qint64 CreatedBefore, const qint64 UpdatedAfter, const qint64 UpdatedBefore, const QString &Status, const QString &SortBy, const QString &SortDirection)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;

    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_GET_ORDERS;
    m_CreatedAfter = CreatedAfter;
    m_CreatedBefore = CreatedBefore;
    m_UpdatedAfter = UpdatedAfter;
    m_UpdatedBefore = UpdatedBefore;
    m_Limit = Limit;
    m_Offset = Offset;
    m_Status = Status;
    m_SortBy = SortBy;
    m_SortDirection = SortDirection;
}

void LazadaApiRequestGetOrders::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_GET_ORDERS);
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
        a_pParams->insert(QString("UpdatedBefore"), convertTimeToStringISO8601(m_UpdatedAfter));
    }

    if (m_Limit >= 0)
    {
        a_pParams->insert(QString("Limit"), QString::number(m_Limit));
    }
    if (m_Offset >= 0)
    {
        a_pParams->insert(QString("Offset"), QString::number(m_Offset));
    }

    if (!m_Status.isEmpty())
    {
        a_pParams->insert(QString("Status"), m_Status);
    }
    if (!m_SortBy.isEmpty())
    {
        a_pParams->insert(QString("SortBy"), m_SortBy);
    }
    if (!m_SortDirection.isEmpty())
    {
        a_pParams->insert(QString("SortDirection"), m_SortDirection);
    }
}
