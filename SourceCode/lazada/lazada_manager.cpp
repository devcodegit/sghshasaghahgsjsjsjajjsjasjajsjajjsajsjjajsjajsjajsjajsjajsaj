#include "lazada_manager.h"
#include "lazada_model.h"
#include "lazada_request.h"
#include "lazada_data_model.h"
#include "../object_listenter.h"

#include <QDateTime>
#include <QDebug>

using namespace Lazada::Control;
using namespace Lazada::Request;
using namespace Lazada::Model;

#define TIME_NEED_REQUEST   2 * 60 * 1000 // 2'

QMutex LazadaManager::_mutexIns;
LazadaManager *LazadaManager::Instance = NULL;
LazadaManager *LazadaManager::instance()
{
    if (!Instance)
    {
        _mutexIns.lock();
        if (!Instance)
        {
            Instance = new LazadaManager();
        }
        _mutexIns.unlock();
    }
    return Instance;
}

LazadaManager::LazadaManager()
{

}

QList<DataOrder *> LazadaManager::getAllOrder(ObjectListenter *objListener)
{
    if ((QDateTime::currentMSecsSinceEpoch() - _timeRequestGetAllOrder) >= TIME_NEED_REQUEST)
    {
        _timeRequestGetAllOrder = QDateTime::currentMSecsSinceEpoch();
        LazadaRequest::instance()->requestGetOrders(objListener);
    }
    return LazadaModel::instance()->getAllOrder();
}

DataOrder *LazadaManager::getOrder(const uint32_t orderId)
{
    return LazadaModel::instance()->getOrder(orderId);
}

QList<DataOrderItem *> LazadaManager::getListOrderItemsWithOrderId(const uint32_t orderId)
{
    return LazadaModel::instance()->getListOrderItemsWithOrderId(orderId);
}

DataOrderItem *LazadaManager::getOrderItem(const uint32_t orderItemId)
{
    return LazadaModel::instance()->getOrderItem(orderItemId);
}

DataOrderItem *LazadaManager::getOrderItem(const QString &trackingCode)
{
    return LazadaModel::instance()->getOrderItem(trackingCode);
}

void LazadaManager::getDocument(QList<uint32_t> orderItems, const QString &documentType, ObjectListenter *objListener)
{
    LazadaRequest::instance()->requestGetDocument(objListener, orderItems, documentType);
}

void LazadaManager::requestOrderItems(QList<uint32_t> listOrderId)
{
    for (int i = 0; i < listOrderId.count(); ++i) {
        LazadaRequest::instance()->requestGetOrderItems(NULL, listOrderId.at(i));
    }
    qDebug() << "requestOrderItems FINISH!";
}

void LazadaManager::updateModelOrder(QList<DataOrder *> listData)
{
    LazadaModel::instance()->addOrder(listData);
}

void LazadaManager::updateModelOrderItem(QList<DataOrderItem *> listData)
{
    if (listData.isEmpty()) return;
    LazadaModel::instance()->addOrderItems(listData.at(0)->getOrderId(), listData);
}

void LazadaManager::requestSetStatusToPackedByMarketplace(QList<uint32_t> listOrderItemId)
{
    LazadaRequest::instance()->requestSetStatusToPackedByMarketplace(NULL, listOrderItemId);
}

void LazadaManager::requestSetStatusToReadyToShip(QList<uint32_t> listOrderItemId)
{
    LazadaRequest::instance()->requestSetStatusToReadyToShip(NULL, listOrderItemId);
}
