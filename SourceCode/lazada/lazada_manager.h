#ifndef LAZADA_MANAGER_H
#define LAZADA_MANAGER_H

#include <qglobal.h>
#include "../global.h"

namespace Core { namespace Listener {
    class ObjectListenter;
}}
using namespace Core::Listener;

namespace Lazada { namespace DataModel {
    class DataOrderItem;
    class DataOrder;
}}
using namespace Lazada::DataModel;

namespace Lazada { namespace Control {

    class LazadaManager
    {
        LazadaManager();
        static LazadaManager *Instance;
        static QMutex _mutexIns;
    public:
        static LazadaManager *instance();

    public:
        QList<DataOrder*> getAllOrder(ObjectListenter *objListener = NULL);
        DataOrder *getOrder(const uint32_t orderId);
        QList<DataOrderItem *> getListOrderItemsWithOrderId(const uint32_t orderId);
        DataOrderItem *getOrderItem(const uint32_t orderItemId);
        DataOrderItem *getOrderItem(const QString &trackingCode);

        void getDocument(QList<uint32_t> orderItems, const QString &documentType, ObjectListenter *objListener = NULL);

        void requestOrderItems(QList<uint32_t> listOrderId);
        void updateModelOrder(QList<DataOrder *> listData);
        void updateModelOrderItem(QList<DataOrderItem *> listData);

        void requestSetStatusToPackedByMarketplace(QList<uint32_t> listOrderItemId);
        void requestSetStatusToReadyToShip(QList<uint32_t> listOrderItemId);

    private:
        qint64 _timeRequestGetAllOrder = -1;
    };

}}

#endif // LAZADA_MANAGER_H
