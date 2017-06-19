#ifndef LAZADA_API_REQUEST_GET_METRICS_H
#define LAZADA_API_REQUEST_GET_METRICS_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestGetMetrics : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestGetMetrics(IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}

#endif // LAZADA_API_REQUEST_GET_METRICS_H
