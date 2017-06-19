#ifndef LAZADA_API_REQUEST_GET_FAILURE_REASONS_H
#define LAZADA_API_REQUEST_GET_FAILURE_REASONS_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestGetFailureReasons : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestGetFailureReasons(IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}

#endif // LAZADA_API_REQUEST_GET_FAILURE_REASONS_H
