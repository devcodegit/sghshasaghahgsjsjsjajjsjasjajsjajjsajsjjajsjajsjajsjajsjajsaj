#ifndef LAZADA_API_REQUEST_REMOVE_PRODUCT_H
#define LAZADA_API_REQUEST_REMOVE_PRODUCT_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestRemoveProduct : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestRemoveProduct(IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}

#endif // LAZADA_API_REQUEST_REMOVE_PRODUCT_H
