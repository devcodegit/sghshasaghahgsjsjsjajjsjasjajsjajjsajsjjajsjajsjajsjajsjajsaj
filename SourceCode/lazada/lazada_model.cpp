#include "lazada_model.h"
#include "lazada_data_model.h"

using namespace Lazada::Model;

QMutex LazadaModel::_mutexIns;
LazadaModel *LazadaModel::Instance = NULL;
LazadaModel *LazadaModel::instance()
{
    if (!Instance)
    {
        _mutexIns.lock();
        if (!Instance)
        {
            Instance = new LazadaModel();
        }
        _mutexIns.unlock();
    }
    return Instance;
}


LazadaModel::LazadaModel()
{

}

void LazadaModel::addOrder(QList<DataOrder *> listOrders)
{
    if (listOrders.isEmpty()) return;
    QMutexLocker locker(&_mutexAddData);
    for (int i = 0; i < listOrders.count(); ++i)
    {
        DataOrder *order = listOrders.at(i);
        if (order)
        {
            addOrder(order->getOrderId(), order, false);
        }
    }
}

void LazadaModel::addOrder(const uint32_t orderId, DataOrder *item, bool isNeedLock)
{
    if (!item) return;

    if (isNeedLock)
        QMutexLocker locker(&_mutexAddData);

    DataOrder *order = _hashOrders.value(orderId, NULL);
    if (order)
    {
        // Da co data item, update...
        updateOrder(order, item);
        delete item;
    }
    else
    {
        // Chua co data item, can add them
        addNewOrder(item);
    }
}

bool LazadaModel::addOrderItems(const uint32_t orderId, QList<DataOrderItem *> orderItems)
{
    if (orderItems.isEmpty()) return false;

    QMutexLocker locker(&_mutexAddData);
    DataOrder *order = _hashOrders.value(orderId, NULL);
    if (order)
    {
        QHash<uint32_t, DataOrderItem *> *hashOrderItems = order->getHashOrderItems();

        if (hashOrderItems)
        {
            for (int i = 0; i < orderItems.count(); ++i)
            {
                DataOrderItem* orderItem = hashOrderItems->value(orderItems.at(i)->getOrderItemId(), NULL);
                if (orderItem)
                {
                    updateOrderItem(orderItem, orderItems.at(i));
                    delete orderItems.at(i);
                }
                else
                {
                    addNewOrderItem(order, orderItem);
                }
            }
        }
        else
        {
            for (int i = 0; i < orderItems.count(); ++i)
            {

                addNewOrderItem(order, orderItems.at(i));
            }
        }
        return true;
    }

    return false;
}

DataOrder *LazadaModel::getOrder(const uint32_t orderId)
{
    QMutexLocker locker(&_mutexAddData);
    return _hashOrders.value(orderId, NULL);
}

QList<DataOrderItem *> LazadaModel::getListOrderItemsWithOrderId(const uint32_t orderId)
{
    DataOrder *order = _hashOrders.value(orderId, NULL);
    if (order)
    {
        return *order->getListOrderItems();
    }
    return QList<DataOrderItem *>();
}

DataOrderItem *LazadaModel::getOrderItem(const uint32_t orderItemId)
{
    return _hashOrdersItems.value(orderItemId, NULL);
}

DataOrderItem *LazadaModel::getOrderItem(const QString &trackingCode)
{
    return NULL;
}

QList<DataOrder *> LazadaModel::getAllOrder(int page, int litmit)
{
    if (litmit > 0 || page > 0)
    {
        // get data theo limit || page
    }
    return _listDataOrder;
}

void LazadaModel::addNewOrder(DataOrder *item)
{
    if (!item) return;
    _hashOrders.insert(item->getOrderId(), item);
    _listDataOrder.append(item);
}

void LazadaModel::addNewOrderItem(DataOrder *order, DataOrderItem *newOrderItem)
{
    if (!order || !newOrderItem) return;

    order->updateOrderItems(newOrderItem);
    _hashOrdersItems.insert(newOrderItem->getOrderItemId(), newOrderItem);
}

void LazadaModel::updateOrderItem(DataOrderItem *oldOrderItem, DataOrderItem *newOrderItem)
{
    if (!oldOrderItem || !newOrderItem) return;
    oldOrderItem->updateData(newOrderItem);
}

void LazadaModel::updateOrder(DataOrder *oldOrder, DataOrder *newOrder)
{
    if (!oldOrder || !newOrder) return;
    oldOrder->updateData(newOrder);
}
