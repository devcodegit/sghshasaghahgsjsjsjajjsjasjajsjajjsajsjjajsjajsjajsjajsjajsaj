#ifndef LAZADA_API_REQUEST_SET_STATUS_TO_PACKED_BY_MARKETPLACE_H
#define LAZADA_API_REQUEST_SET_STATUS_TO_PACKED_BY_MARKETPLACE_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestSetStatusToPackedByMarketplace : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestSetStatusToPackedByMarketplace(IApiRequestListener *a_pListener,
                                                       QList<int> OrderItemIds,
                                                       const QString &DeliveryType = "",
                                                       const QString &ShippingProvider = "");
        virtual void generateParams(QHash<QString, QString>* a_pParams);

    private:
        QList<int> m_OrderItemIds;
        QString m_DeliveryType;
        QString m_ShippingProvider;
    };

}}
#endif // LAZADA_API_REQUEST_SET_STATUS_TO_PACKED_BY_MARKETPLACE_H
