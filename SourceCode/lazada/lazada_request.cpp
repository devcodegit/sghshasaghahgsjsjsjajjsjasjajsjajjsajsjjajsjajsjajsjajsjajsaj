#include "lazada_request.h"
#include "lazada_request_api_factory.h"
#include "lazada_parser_factory.h"
#include "lazada_model.h"
#include "lazada_manager.h"
#include "lazada_data_model.h"
#include "../object_listenter.h"
#include "../core/request/apirequest_worker.h"
#include "../lazada/lazada_api_command_defined.h"
#include "../lazada/request/lazada_api_request_get_orders.h"
#include "../lazada/request/lazada_api_request_get_order.h"
#include "../lazada/dataitem/lazada_data_item_list_order.h"
#include "../lazada/dataitem/lazada_data_item_order.h"
#include "../lazada/dataitem/lazada_data_item_order_items.h"
#include "../lazada/dataitem/lazada_data_item_bill_order.h"
#include "../lazada/dataitem/lazada_data_item_get_document.h"

using namespace Lazada::Request;
using namespace Lazada::Api;
using namespace Lazada::Control;
using namespace Core::Lazada::Request;
using namespace Core::Lazada::Parser;

QMutex LazadaRequest::mutexIns;
LazadaRequest *LazadaRequest::Instance = NULL;
LazadaRequest *LazadaRequest::instance()
{
    if (!Instance)
    {
        mutexIns.lock();
        if (!Instance)
        {
            Instance = new LazadaRequest();
        }
        mutexIns.unlock();
    }
    return Instance;
}

LazadaRequest::LazadaRequest()
{

}

void LazadaRequest::requestGetOrders(ObjectListenter *pListener, const int page, const int limit)
{
    Q_UNUSED(page);
    Q_UNUSED(limit);

    auto request = LazadaRequestApiFactory::lazadaCreateApiRequestListOrder(this);
    request->setParser(LazadaParserFactory::lazadaCreateParserListOrder());

    _pCurListenerGetOrder = pListener;
    _iCurRequestIdGetListOrder = request->getRequestId();

    ApiRequestWorker::instance()->AddRequest(request);
}

void LazadaRequest::requestGetOrderItems(ObjectListenter *pListener, const uint32_t orderId)
{
    qDebug() << "LazadaRequest::requestGetOrderItems = " << orderId;
    auto request = LazadaRequestApiFactory::lazadaCreateApiRequestOrderItems(orderId, this);
    request->setParser(LazadaParserFactory::lazadaCreateParserOrderItems());

    _pCurListenerGetOrderItems = pListener;
    _iCurRequestIdGetOrderItems = request->getRequestId();

    ApiRequestWorker::instance()->AddRequest(request);
}

void LazadaRequest::requestSetStatusToPackedByMarketplace(ObjectListenter *pListener, QList<uint32_t> listOrderItems)
{
    Q_UNUSED(pListener);
    if (listOrderItems.isEmpty()) return;
    DataOrderItem *orderItem = LazadaManager::instance()->getOrderItem(listOrderItems.at(0));
    if (orderItem)
    {
        auto request = LazadaRequestApiFactory::lazadaSetStatusToPackedByMarketplace(listOrderItems,
                                                                                     orderItem->getShippingType(),
                                                                                     orderItem->getShipmentProvider(),
                                                                                     this);
        ApiRequestWorker::instance()->AddRequest(request);
    }
}

void LazadaRequest::requestSetStatusToReadyToShip(ObjectListenter *pListener, QList<uint32_t> listOrderItems)
{
    Q_UNUSED(pListener);
    if (listOrderItems.isEmpty()) return;
    DataOrderItem *orderItem = LazadaManager::instance()->getOrderItem(listOrderItems.at(0));
    if (orderItem)
    {
        auto request = LazadaRequestApiFactory::lazadaSetStatusToReadyToShip(listOrderItems,
                                                                             orderItem->getShippingType(),
                                                                             orderItem->getShipmentProvider(),
                                                                             orderItem->getTrackingCode(),
                                                                             "",
                                                                             this);
        ApiRequestWorker::instance()->AddRequest(request);
    }
}

void LazadaRequest::requestGetDocument(ObjectListenter *pListener, QList<uint32_t> listOrderItems, const QString &DocumentType)
{
    if (listOrderItems.isEmpty()) return;
    DataOrderItem *orderItem = LazadaManager::instance()->getOrderItem(listOrderItems.at(0));
    if (orderItem)
    {
        qDebug() << "request document";
        auto request = LazadaRequestApiFactory::lazadaGetDocument(this,
                                                                  listOrderItems,
                                                                  DocumentType);
        _hashListenerGetDocument.insert(request->getRequestId(), pListener);
        request->setParser(LazadaParserFactory::lazadaCreateParserGetDocument());
        ApiRequestWorker::instance()->AddRequest(request);
    }
}

void LazadaRequest::OnApiRequestComplete(IApiRequest *a_pRequest)
{
    if (!a_pRequest) return;
    int requestType = a_pRequest->getRequestType();
    switch (requestType)
    {
    case LazadaApiCommandDefined::LAZADA_REQ_GET_ORDERS:
    {
        handleResponseApiListOrder(a_pRequest);
        break;
    }

    case LazadaApiCommandDefined::LAZADA_REQ_SET_STATUS_TO_PACKED_BY_MARKETPLACE:
    {
        handleResponseApiSetStatusToPackedByMarketplace(a_pRequest);
        break;
    }

    case LazadaApiCommandDefined::LAZADA_REQ_GET_ORDER_ITEMS:
    {
        handleResponseApiOrderItems(a_pRequest);
        break;
    }

    case LazadaApiCommandDefined::LAZADA_REQ_GET_DOCUMENT:
    {
        handleResponseApiGetDocument(a_pRequest);
        break;
    }

    default:
        break;
    }
}

void LazadaRequest::OnApiRequestError(IApiRequest *a_pRequest)
{
    Q_UNUSED(a_pRequest);
}

void LazadaRequest::handleResponseApiListOrder(IApiRequest *a_pRequest)
{
    int requestId = a_pRequest->getRequestId();
    if (requestId == _iCurRequestIdGetListOrder)
    {
        int errorCode = a_pRequest->getErrorCode();
        switch (errorCode)
        {

        case 0:
        {
            LazadaDataItemListOrder *dataItem = (LazadaDataItemListOrder*)a_pRequest->getDataItem();
            if (dataItem)
            {
                QList<LazadaDataItemOrder *> listData = dataItem->getListData();
                QList<DataOrder *> listNewOrder;
                QList<uint32_t> listRequestOrderItems;

                for (int i = 0; i < listData.count(); ++i)
                {
                    LazadaDataItemOrder *item = listData.at(i);
                    if (item)
                    {
                        DataOrder *order = LazadaManager::instance()->getOrder(item->OrderId());
                        if (!order)
                        {
                            order = new DataOrder();
                            order->setOrderId(item->OrderId());
                            order->setOrderNumber(item->getOrderNumber());
                            order->setItemCount(item->getItemsCount());
                            order->setCreatedAt(item->getCreatedAt());
                            order->setUpdatedAt(item->getUpdatedAt());
                            order->setCustomerFullName(item->getCustomerLastName() + item->getCustomerFirstName());
                            order->setPaymentMethod(item->getPaymentMethod());
                            order->setGiftMessage(item->getGiftMessage());
                            order->setGiftOption(item->getGiftOption());
                            order->setVoucherCode(item->getVoucherCode());
                            order->setPrice(item->getPrice());

                            listNewOrder.append(order);
                            listRequestOrderItems.append(item->OrderId());

                        }
                        else
                        {
                            // Todo: update
                        }

                        delete item;
                        item = NULL;
                    }

                }

                if (!listNewOrder.isEmpty())
                {
                    LazadaManager::instance()->updateModelOrder(listNewOrder);
                }

                if (!listRequestOrderItems.isEmpty())
                {
                    LazadaManager::instance()->requestOrderItems(listRequestOrderItems);
                }

                if (_pCurListenerGetOrder)
                {
                    _pCurListenerGetOrder->OnRequestCompleted(new ResultListener(a_pRequest->getRequestType(),
                                                                         a_pRequest->getErrorCode(),
                                                                         a_pRequest->getErrorMessage()));
                    _pCurListenerGetOrder = NULL;
                }
            }
            break;
        }

        default:
            break;
        }
        _iCurRequestIdGetListOrder = -1;
    }
}

void LazadaRequest::handleResponseApiOrderItems(IApiRequest *a_pRequest)
{
//    int requestId = a_pRequest->getRequestId();
//    if (requestId == _iCurRequestIdGetOrderItems)
    {
        int errorCode = a_pRequest->getErrorCode();
        switch (errorCode)
        {

        case 0:
        {
            LazadaDataItemOrderItems *dataItem = (LazadaDataItemOrderItems*)a_pRequest->getDataItem();
            if (dataItem)
            {
                QList<LazadaDataItemBillOrder *> listData = dataItem->getListData();
                QList<DataOrderItem *> listNewOrderItems;
                for (int i = 0; i < listData.count(); ++i)
                {
                    LazadaDataItemBillOrder *item = listData.at(i);
                    if (item)
                    {
                        DataOrderItem *oldItem = LazadaManager::instance()->getOrderItem(item->OrderItemId());
                        if (!oldItem)
                        {
                            oldItem = new DataOrderItem();
                            oldItem->setOrderItemId(item->OrderItemId());
                            oldItem->setShopId(item->ShopId());
                            oldItem->setOrderId(item->OrderId());
                            oldItem->setNameOrderItem(item->Name());
                            oldItem->setSku(item->Sku());
                            oldItem->setShopSku(item->ShopSku());
                            oldItem->setShippingType(item->ShippingType());
                            oldItem->setStatus(item->Status());
                            oldItem->setShipmentProvider(item->ShipmentProvider());
                            oldItem->setTrackingCode(item->TrackingCode());
                            oldItem->setPurchaseOrderId(item->PurchaseOrderId());
                            oldItem->setPurchaseOrderNumber(item->PurchaseOrderNumber());
                            oldItem->setPackageId(item->PackageId());
                            oldItem->setCreatedAt(item->CreatedAt());
                            oldItem->setUpdatedAt(item->UpdatedAt());
                            oldItem->setProductMainImage(item->productMainImage());
                            oldItem->setProductDetailUrl(item->ProductDetailUrl());
                            oldItem->setInvoiceNumber(item->invoiceNumber());

                            listNewOrderItems.append(oldItem);
                        }
                        else
                        {

                        }

                        delete item;
                        item = NULL;
                    }

                }

                if (!listNewOrderItems.isEmpty())
                {
                    LazadaManager::instance()->updateModelOrderItem(listNewOrderItems);
                }
            }
            break;
        }

        default:
            break;
        }
        _iCurRequestIdGetOrderItems = -1;
    }
}

void LazadaRequest::handleResponseApiGetDocument(IApiRequest *a_pRequest)
{
    int requestId = a_pRequest->getRequestId();
    ObjectListenter *objListener = _hashListenerGetDocument.value(requestId, NULL);
    if (_hashListenerGetDocument.contains(requestId))
    {
        int errorCode = a_pRequest->getErrorCode();
        switch (errorCode) {
        case 0:
        {
            LazadaDataItemGetDocument *dataItem = (LazadaDataItemGetDocument*)a_pRequest->getDataItem();
            if (dataItem)
            {
                if (objListener)
                {
                    objListener->OnRequestCompleted(new ResultListener(a_pRequest->getRequestType(),
                                                                       a_pRequest->getErrorCode(),
                                                                       a_pRequest->getErrorMessage(),
                                                                       dataItem->getPathFile()));
                }
            }
            _hashListenerGetDocument.remove(requestId);
            break;
        }
        default:
            break;
        }
    }
}

void LazadaRequest::handleResponseApiSetStatusToPackedByMarketplace(IApiRequest *a_pRequest)
{
    int requestId = a_pRequest->getRequestId();
    if (_hashIdRequestSetStatusToPackedByMarketplace.contains(requestId))
    {
        int errorCode = a_pRequest->getErrorCode();
        switch (errorCode) {
        case 0:
        {

            _hashIdRequestSetStatusToPackedByMarketplace.remove(requestId);
            break;
        }
        default:
            break;
        }
    }
}
