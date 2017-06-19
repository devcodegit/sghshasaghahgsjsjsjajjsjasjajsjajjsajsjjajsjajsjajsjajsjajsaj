#ifndef LAZADA_API_REQUEST_SET_IMAGES_H
#define LAZADA_API_REQUEST_SET_IMAGES_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestSetImages : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestSetImages(IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}

#endif // LAZADA_API_REQUEST_SET_IMAGES_H
