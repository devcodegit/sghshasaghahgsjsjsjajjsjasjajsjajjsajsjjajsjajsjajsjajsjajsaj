#ifndef LAZADA_REQUEST_API_FACTORY_H
#define LAZADA_REQUEST_API_FACTORY_H

#include "../global.h"
#include "qglobal.h"
#include <QList>
#include <QString>
namespace Core { namespace Request {
    class ApiRequest;
    class IApiRequestListener;
}}

using namespace Core::Request;

namespace Core { namespace Lazada { namespace Request {

    class LazadaRequestApiFactory
    {
    public:
        static ApiRequest *lazadaCreateApiRequestListOrder(IApiRequestListener *listener);
        static ApiRequest *lazadaCreateApiRequestOrder(int orderId, IApiRequestListener *listener);
        static ApiRequest *lazadaCreateApiRequestOrderItems(int orderId, IApiRequestListener *listener);
        static ApiRequest *lazadaSetStatusToPackedByMarketplace(QList<uint32_t> listOrderItemId, const QString &DeliveryType, const QString &ShippingProvider, IApiRequestListener *listener);
        static ApiRequest *lazadaSetStatusToReadyToShip(QList<uint32_t> listOrderItemId, const QString &DeliveryType, const QString &ShippingProvider, const QString &TrackingNumber, const QString &SerialNumber, IApiRequestListener *listener);
        static ApiRequest *lazadaGetDocument(IApiRequestListener *listener, QList<uint32_t> listOrderItemId, const QString &DocumentType);
    };

}}}

#endif // LAZADA_REQUEST_API_FACTORY_H
