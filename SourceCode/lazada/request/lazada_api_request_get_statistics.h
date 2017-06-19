#ifndef LAZADA_API_REQUEST_GET_STATISTICS_H
#define LAZADA_API_REQUEST_GET_STATISTICS_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestGetStatistics : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestGetStatistics(IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}

#endif // LAZADA_API_REQUEST_GET_STATISTICS_H
