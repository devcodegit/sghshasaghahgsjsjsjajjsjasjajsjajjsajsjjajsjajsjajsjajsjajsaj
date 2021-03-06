#ifndef LAZADA_API_REQUEST_ORDER_H
#define LAZADA_API_REQUEST_ORDER_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestGetOrder : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestGetOrder(int orderId, IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);

    private:
        int m_orderId = -1;
    };

}}
#endif // LAZADA_API_REQUEST_ORDER_H
