#ifndef LAZADA_API_REQUEST_SET_STATUS_TO_READY_TO_SHIP_H
#define LAZADA_API_REQUEST_SET_STATUS_TO_READY_TO_SHIP_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestSetStatusToReadyToShip : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestSetStatusToReadyToShip(IApiRequestListener *a_pListener,
                                               QList<int> OrderItemIds,
                                               const QString &DeliveryType =  "",
                                               const QString &ShippingProvider = "",
                                               const QString &TrackingNumber = "");
        virtual void generateParams(QHash<QString, QString>* a_pParams);

    private:
        QList<int> m_OrderItemIds;
        QString m_DeliveryType;
        QString m_ShippingProvider;
        QString m_TrackingNumber;
        QString m_SerialNumber;
    };

}}
#endif // LAZADA_API_REQUEST_SET_STATUS_TO_READY_TO_SHIP_H
