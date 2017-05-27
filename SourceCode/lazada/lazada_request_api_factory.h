#ifndef LAZADA_REQUEST_API_FACTORY_H
#define LAZADA_REQUEST_API_FACTORY_H

namespace Core { namespace Request {
    class ApiRequest;
    class IApiRequestListener;
}}

using namespace Core::Request;

namespace Core { namespace Lazada { namespace Request {

    class LazadaRequestApiFactory
    {
    public:
        static ApiRequest *lazadaCreateApiRequestListOrder(IApiRequestListener *listener);
        static ApiRequest *lazadaCreateApiRequestOrder(int orderId, IApiRequestListener *listener);
        static ApiRequest *lazadaCreateApiRequestOrderItems(int orderId, IApiRequestListener *listener);
    };

}}}

#endif // LAZADA_REQUEST_API_FACTORY_H
