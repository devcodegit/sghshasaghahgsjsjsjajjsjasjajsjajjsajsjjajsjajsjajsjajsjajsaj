#ifndef LAZADA_API_REQUEST_UPDATE_PRICE_QUANTITY_H
#define LAZADA_API_REQUEST_UPDATE_PRICE_QUANTITY_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestUpdatePriceQuantity : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestUpdatePriceQuantity(IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}

#endif // LAZADA_API_REQUEST_UPDATE_PRICE_QUANTITY_H
