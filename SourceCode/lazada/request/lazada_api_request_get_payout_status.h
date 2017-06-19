#ifndef LAZADA_API_REQUEST_GET_PAYOUT_STATUS_H
#define LAZADA_API_REQUEST_GET_PAYOUT_STATUS_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestGetPayoutStatus : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestGetPayoutStatus(IApiRequestListener *a_pListener, const qint64 CreatedAfter = 0);
        virtual void generateParams(QHash<QString, QString>* a_pParams);

    private:
        qint64 m_CreatedAfter = 0;
    };

}}

#endif // LAZADA_API_REQUEST_GET_PAYOUT_STATUS_H
