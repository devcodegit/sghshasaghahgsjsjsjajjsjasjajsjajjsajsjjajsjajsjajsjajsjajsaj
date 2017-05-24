#include "lazada_api_request_list_order.h"
#include "../../core/service_map_manager.h"
#include "../lazada_define.h"

#include <QDateTime>

using namespace Core::Request;
using namespace Core::Service;

LazadaApiRequestListOrder::LazadaApiRequestListOrder(IApiRequestListener *a_pListener)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;
}

void LazadaApiRequestListOrder::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), "GetOrders");
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);
}
