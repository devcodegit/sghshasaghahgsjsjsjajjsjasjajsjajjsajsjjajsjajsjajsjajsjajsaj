#include "lazada_api_request_set_status_to_packed_by_marketplace.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

#include <QList>

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestSetStatusToPackedByMarketplace::LazadaApiRequestSetStatusToPackedByMarketplace(IApiRequestListener *a_pListener, QList<uint32_t> OrderItemIds, const QString &DeliveryType, const QString &ShippingProvider)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;

    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_SET_STATUS_TO_PACKED_BY_MARKETPLACE;
    m_DeliveryType = DeliveryType;
    m_ShippingProvider = ShippingProvider;
    m_OrderItemIds.append(OrderItemIds);
}

void LazadaApiRequestSetStatusToPackedByMarketplace::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_SET_STATUS_TO_PACKED_BY_MARKETPLACE);
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);
    a_pParams->insert(QString("ShippingProvider"), m_ShippingProvider);
    a_pParams->insert(QString("DeliveryType"), m_DeliveryType);
    a_pParams->insert(QString("OrderItemIds"), convertListToString(m_OrderItemIds));
    qDebug() << "LazadaApiRequestSetStatusToPackedByMarketplace::generateParams";
}
