#ifndef LAZADA_API_REQUEST_MIGRATE_IMAGE_H
#define LAZADA_API_REQUEST_MIGRATE_IMAGE_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestMigrateImage : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestMigrateImage(IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}

#endif // LAZADA_API_REQUEST_MIGRATE_IMAGE_H
