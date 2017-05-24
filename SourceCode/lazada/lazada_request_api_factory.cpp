#include "lazada_request_api_factory.h"
#include "request/lazada_api_request_list_order.h"

using namespace Core::Lazada::Request;

ApiRequest *LazadaRequestApiFactory::lazadaCreateApiRequestListOrder(IApiRequestListener *listener)
{
    LazadaApiRequestListOrder *request =  new LazadaApiRequestListOrder(listener);
    return request;
}
