#include "lazada_request_api_factory.h"
#include "request/lazada_api_request_list_order.h"
#include "request/lazada_api_request_order.h"
#include "request/lazada_api_request_order_items.h"

using namespace Core::Lazada::Request;

ApiRequest *LazadaRequestApiFactory::lazadaCreateApiRequestListOrder(IApiRequestListener *listener)
{
    LazadaApiRequestListOrder *request =  new LazadaApiRequestListOrder(listener);
    return request;
}

ApiRequest *LazadaRequestApiFactory::lazadaCreateApiRequestOrder(int orderId, IApiRequestListener *listener)
{
    LazadaApiRequestOrder *request =  new LazadaApiRequestOrder(orderId, listener);
    return request;
}

ApiRequest *LazadaRequestApiFactory::lazadaCreateApiRequestOrderItems(int orderId, IApiRequestListener *listener)
{
    LazadaApiRequestOrderItems *request =  new LazadaApiRequestOrderItems(orderId, listener);
    return request;
}
