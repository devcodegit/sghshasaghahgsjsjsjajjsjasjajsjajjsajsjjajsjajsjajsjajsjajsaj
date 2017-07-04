#ifndef LAZADA_MODEL_H
#define LAZADA_MODEL_H

#include <QHash>
#include <qglobal.h>
#include "../global.h"

namespace Lazada { namespace DataModel {
    class DataOrderItem;
    class DataOrder;
}}
using namespace Lazada::DataModel;

namespace Lazada { namespace Model {

    class LazadaModel
    {
        LazadaModel();
        static LazadaModel *Instance;
        static QMutex _mutexIns;
    public:
        static LazadaModel *instance();

        void addOrder(QList<DataOrder *> listOrders);
        void addOrder(const uint32_t orderId, DataOrder *item, bool isNeedLock = true);
        bool addOrderItems(const uint32_t orderId, QList<DataOrderItem *> orderItems);

        QList<DataOrder *> getAllOrder(int page = 0, int litmit = -1);
        DataOrder *getOrder(const uint32_t orderId);
        QList<DataOrderItem *> getListOrderItemsWithOrderId(const uint32_t orderId);
        DataOrderItem *getOrderItem(const uint32_t orderItemId);
        DataOrderItem *getOrderItem(const QString &trackingCode);

    private:
        void addNewOrder(DataOrder *item);
        void addNewOrderItem(DataOrder *order, DataOrderItem *newOrderItem);
        void updateOrderItem(DataOrderItem *oldOrderItem, DataOrderItem *newOrderItem);
        void updateOrder(DataOrder *oldOrder, DataOrder *newOrder);

    private:
        QHash<uint32_t, DataOrder *> _hashOrders;
        QHash<uint32_t, DataOrderItem *> _hashOrdersItems;
        QList<DataOrder *> _listDataOrder;

        QMutex _mutexAddData;
    };

}}


#endif // LAZADA_MODEL_H
