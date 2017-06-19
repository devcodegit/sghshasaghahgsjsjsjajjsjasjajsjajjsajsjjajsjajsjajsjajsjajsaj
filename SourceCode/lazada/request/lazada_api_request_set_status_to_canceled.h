#ifndef LAZADA_API_REQUEST_SET_STATUS_TO_CANCELED_H
#define LAZADA_API_REQUEST_SET_STATUS_TO_CANCELED_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestSetStatusToCanceled : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestSetStatusToCanceled(IApiRequestListener *a_pListener, const qint64 OrderItemId, const QString &Reason = "", const QString &ReasonDetail = "");
        virtual void generateParams(QHash<QString, QString>* a_pParams);

    private:
        qint64 m_OrderItemId = -1;
        QString m_Reason;
        QString m_ReasonDetail;
    };

}}
#endif // LAZADA_API_REQUEST_SET_STATUS_TO_CANCELED_H
