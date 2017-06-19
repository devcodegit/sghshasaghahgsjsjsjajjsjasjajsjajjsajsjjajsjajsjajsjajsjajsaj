#ifndef LAZADA_API_REQUEST_USER_UPDATE_H
#define LAZADA_API_REQUEST_USER_UPDATE_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestUserUpdate : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestUserUpdate(IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}

#endif // LAZADA_API_REQUEST_USER_UPDATE_H
