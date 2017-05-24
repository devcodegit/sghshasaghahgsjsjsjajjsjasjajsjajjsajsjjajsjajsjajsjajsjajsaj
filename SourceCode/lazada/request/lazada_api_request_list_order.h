#ifndef LAZADA_API_REQUEST_LIST_ORDER_H
#define LAZADA_API_REQUEST_LIST_ORDER_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestListOrder : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestListOrder(IApiRequestListener *a_pListener);

        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}

#endif // LAZADA_API_REQUEST_LIST_ORDER_H
