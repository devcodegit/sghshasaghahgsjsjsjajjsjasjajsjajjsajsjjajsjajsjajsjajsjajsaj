#ifndef LAZADA_API_REQUEST_UPDATE_PRODUCT_H
#define LAZADA_API_REQUEST_UPDATE_PRODUCT_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestUpdateProduct : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestUpdateProduct(IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}

#endif // LAZADA_API_REQUEST_UPDATE_PRODUCT_H
