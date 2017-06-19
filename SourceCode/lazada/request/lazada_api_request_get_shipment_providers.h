#ifndef LAZADA_API_REQUEST_GET_SHIPMENT_PROVIDERS_H
#define LAZADA_API_REQUEST_GET_SHIPMENT_PROVIDERS_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestGetShipmentProviders : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestGetShipmentProviders(IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}
#endif // LAZADA_API_REQUEST_GET_SHIPMENT_PROVIDERS_H
