#include "lazada_request_api_factory.h"
#include "request/lazada_api_request_get_orders.h"
#include "request/lazada_api_request_get_order.h"
#include "request/lazada_api_request_order_items.h"
#include "request/lazada_api_request_set_status_to_packed_by_marketplace.h"
#include "request/lazada_api_request_set_status_to_ready_to_ship.h"
#include "request/lazada_api_request_get_document.h"

using namespace Core::Lazada::Request;

ApiRequest *LazadaRequestApiFactory::lazadaCreateApiRequestListOrder(IApiRequestListener *listener)
{
    LazadaApiRequestGetOrders *request =  new LazadaApiRequestGetOrders(listener, 100);
    return request;
}

ApiRequest *LazadaRequestApiFactory::lazadaCreateApiRequestOrder(int orderId, IApiRequestListener *listener)
{
    LazadaApiRequestGetOrder *request =  new LazadaApiRequestGetOrder(orderId, listener);
    return request;
}

ApiRequest *LazadaRequestApiFactory::lazadaCreateApiRequestOrderItems(int orderId, IApiRequestListener *listener)
{
    LazadaApiRequestOrderItems *request =  new LazadaApiRequestOrderItems(orderId, listener);
    return request;
}

ApiRequest *LazadaRequestApiFactory::lazadaSetStatusToPackedByMarketplace(QList<uint32_t> listOrderItemId, const QString &DeliveryType, const QString &ShippingProvider, IApiRequestListener *listener)
{
    LazadaApiRequestSetStatusToPackedByMarketplace *request = new LazadaApiRequestSetStatusToPackedByMarketplace(listener,listOrderItemId, DeliveryType, ShippingProvider);
    return request;
}

ApiRequest *LazadaRequestApiFactory::lazadaSetStatusToReadyToShip(QList<uint32_t> listOrderItemId, const QString &DeliveryType, const QString &ShippingProvider, const QString &TrackingNumber, const QString &SerialNumber, IApiRequestListener *listener)
{
    LazadaApiRequestSetStatusToReadyToShip *request = new LazadaApiRequestSetStatusToReadyToShip(listener,
                                                                                                 listOrderItemId,
                                                                                                 DeliveryType,
                                                                                                 ShippingProvider,
                                                                                                 TrackingNumber,
                                                                                                 SerialNumber);
    return request;
}

ApiRequest *LazadaRequestApiFactory::lazadaGetDocument(IApiRequestListener *listener, QList<uint32_t> listOrderItemId, const QString &DocumentType)
{
    LazadaApiRequestGetDocument *request = new LazadaApiRequestGetDocument(listener,listOrderItemId, DocumentType);
    return request;
}
