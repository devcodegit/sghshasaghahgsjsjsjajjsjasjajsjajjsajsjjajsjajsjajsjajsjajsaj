#include "lazada_request_api_factory.h"
#include "request/lazada_api_request_get_orders.h"
#include "request/lazada_api_request_get_order.h"
#include "request/lazada_api_request_order_items.h"

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
