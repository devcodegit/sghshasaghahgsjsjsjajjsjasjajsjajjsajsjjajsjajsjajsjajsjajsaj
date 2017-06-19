#include "lazada_api_request_set_status_to_ready_to_ship.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestSetStatusToReadyToShip::LazadaApiRequestSetStatusToReadyToShip(IApiRequestListener *a_pListener, QList<int> OrderItemIds, const QString &DeliveryType, const QString &ShippingProvider, const QString &TrackingNumber)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;

    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_SET_STATUS_TO_READY_TO_SHIP;
    m_OrderItemIds = OrderItemIds;
    m_ShippingProvider = ShippingProvider;
    m_TrackingNumber = TrackingNumber;
    m_DeliveryType = DeliveryType;
//    m_SerialNumber //chua biet support
}

void LazadaApiRequestSetStatusToReadyToShip::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_SET_STATUS_TO_READY_TO_SHIP);
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);
    a_pParams->insert(QString("DeliveryType"), m_DeliveryType);
    a_pParams->insert(QString("ShippingProvider"), m_ShippingProvider);
    a_pParams->insert(QString("TrackingNumber"), m_TrackingNumber);
//    a_pParams->insert(QString("SerialNumber"),);
//    a_pParams->insert(QString("OrderItemIds"), );
}
