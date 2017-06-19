#ifndef LAZADA_API_REQUEST_SELLER_UPDATE_H
#define LAZADA_API_REQUEST_SELLER_UPDATE_H


#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestSellerUpdate : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestSellerUpdate(IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}

#endif // LAZADA_API_REQUEST_SELLER_UPDATE_H
