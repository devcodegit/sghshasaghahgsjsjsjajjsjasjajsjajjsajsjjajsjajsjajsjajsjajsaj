#include "lazada_handler.h"
#include "lazada_request_api_factory.h"
#include "lazada_parser_factory.h"
#include "../core/request/apirequest_worker.h"
#include "../core/request/apirequest.h"
#include "../lazada/lazada_api_command_defined.h"
#include "../lazada/request/lazada_api_request_get_orders.h"
#include "../lazada/request/lazada_api_request_get_order.h"
#include "../lazada/request/lazada_api_request_order_items.h"
#include "../lazada/dataitem/lazada_data_item_list_order.h"
#include "../lazada/dataitem/lazada_data_item_order.h"
#include "../lazada/dataitem/lazada_data_item_order_items.h"
#include "../lazada/dataitem/lazada_data_item_bill_order.h"

#include <QDateTime>

#define TIME_NEED_REQUEST   2 * 60 * 1000 // 2'

using namespace Core::Request;
using namespace Core::Lazada::Request;
using namespace Core::Lazada::Parser;
using namespace Lazada::Controls;
using namespace Lazada::Api;

QMutex LazadaHandler::mutexIns;
LazadaHandler *LazadaHandler::Instance = NULL;
LazadaHandler *LazadaHandler::instance()
{
    if (!Instance)
    {
        mutexIns.lock();
        if (!Instance)
        {
            Instance = new LazadaHandler();
        }
        mutexIns.unlock();
    }
    return Instance;
}

LazadaHandler::LazadaHandler()
{

}

QList<LazadaDataItemOrder *> LazadaHandler::getAllDataOrders(IObjRequestListener *pListener)
{
    if ((QDateTime::currentMSecsSinceEpoch() - _timeRequestAllListOrder) >= TIME_NEED_REQUEST)
    {
        _timeRequestAllListOrder = QDateTime::currentMSecsSinceEpoch();
        requestListOrder(pListener);
    }
    return _listDataOrders;
}

LazadaDataItemOrder *LazadaHandler::getDataOrder(const qint64 orderId, IObjRequestListener *pListener)
{
    LazadaDataItemOrder *dataOrder = _hashDataOrders.value(orderId, NULL);
    if (!dataOrder)
    {
        requestOrder(orderId, pListener);
    }
    return dataOrder;
}

LazadaDataItemBillOrder *LazadaHandler::getBillOrder(const qint64 orderId, IObjRequestListener *pListener)
{
    LazadaDataItemBillOrder *itemdata = _hashDataOrderItems.value(orderId, NULL);
    if ((QDateTime::currentMSecsSinceEpoch() - _timeRequestAllOrderItems) > TIME_NEED_REQUEST || !itemdata)
    {
        requestOrderItems(orderId, pListener);
    }
    return itemdata;
}

void LazadaHandler::requestListOrder(IObjRequestListener *pListener)
{
    qDebug() << "LazadaHandler::requestListOrder";
    auto request = LazadaRequestApiFactory::lazadaCreateApiRequestListOrder(this);
    request->setParser(LazadaParserFactory::lazadaCreateParserListOrder());

    _curRequestIdGetListOrder = request->getRequestId();
    _hashOjectListener.insert(_curRequestIdGetListOrder, pListener);

    ApiRequestWorker::instance()->AddRequest(request);
}

void LazadaHandler::requestOrder(int orderId, IObjRequestListener *pListener)
{
    qDebug() << "LazadaHandler::requestOrder";
    auto request = LazadaRequestApiFactory::lazadaCreateApiRequestOrder(orderId, this);
    request->setParser(LazadaParserFactory::lazadaCreateParserListOrder());

    _curRequestIdGetOrder = request->getRequestId();
    _hashOjectListener.insert(_curRequestIdGetOrder, pListener);

    ApiRequestWorker::instance()->AddRequest(request);
}

void LazadaHandler::requestOrderItems(int orderId, IObjRequestListener *pListener)
{
    qDebug() << "LazadaHandler::requestOrderItems";
    auto request = LazadaRequestApiFactory::lazadaCreateApiRequestOrderItems(orderId, this);
    request->setParser(LazadaParserFactory::lazadaCreateParserOrderItems());

    _curRequestIdGetOrderItems = request->getRequestId();
    _hashOjectListener.insert(_curRequestIdGetOrderItems, pListener);

    ApiRequestWorker::instance()->AddRequest(request);
}

void LazadaHandler::handleResponseApiListOrder(IApiRequest *a_pRequest)
{
    int requestId = a_pRequest->getRequestId();
    if (requestId == _curRequestIdGetListOrder)
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
                for (int i = 0; i < listData.count(); ++i)
                {
                    LazadaDataItemOrder *item = listData.at(i);
                    if (item)
                    {
                        LazadaDataItemOrder *dataOld = _hashDataOrders.value(item->OrderId(), NULL);
                        if (!dataOld)
                        {
                            dataOld = (LazadaDataItemOrder*)item->clone();
                            _hashDataOrders.insert(dataOld->OrderId(), dataOld);
                            _listDataOrders.append(dataOld);
                        }
                        else
                        {
                            item->cloneData(dataOld);
                        }

                        delete item;
                        item = NULL;
                    }

                }

                IObjRequestListener *pObjListener = _hashOjectListener.value(requestId, NULL);
                if (pObjListener)
                {
                    ResponseResult *response = new ResponseResult(a_pRequest->getRequestType(),
                                                                  a_pRequest->getErrorMessage());
                    pObjListener->OnRequestCompleted(response);
                }
            }
            _hashOjectListener.remove(requestId);
            break;
        }

        default:
            break;
        }
        _curRequestIdGetListOrder = -1;
    }
}

void LazadaHandler::handleResponseApiOrder(IApiRequest *a_pRequest)
{
    int requestId = a_pRequest->getRequestId();
    if (requestId == _curRequestIdGetOrder)
    {
        int errorCode = a_pRequest->getErrorCode();
        switch (errorCode)
        {

        case 0:
        {
            LazadaDataItemOrder *dataItem = (LazadaDataItemOrder*)a_pRequest->getDataItem();
            if (dataItem)
            {
                LazadaDataItemOrder *dataOld = _hashDataOrders.value(dataItem->OrderId(), NULL);
                if (!dataOld)
                {
                    dataOld = (LazadaDataItemOrder*)dataItem->clone();
                    _hashDataOrders.insert(dataOld->OrderId(), dataOld);
                    _listDataOrders.append(dataOld);
                }
                else
                {
                    //Todo: update data
                    dataItem->cloneData(dataOld);
                }

                IObjRequestListener *pObjListener = _hashOjectListener.value(requestId, NULL);
                if (pObjListener)
                {
                    ResponseResult *response = new ResponseResult(a_pRequest->getRequestType(),
                                                                  a_pRequest->getErrorMessage());
                    pObjListener->OnRequestCompleted(response);
                }
            }
            _hashOjectListener.remove(requestId);
            break;
        }

        default:
            break;
        }
        _curRequestIdGetOrder = -1;
    }
}

void LazadaHandler::handleResponseApiOrderItems(IApiRequest *a_pRequest)
{
    int requestId = a_pRequest->getRequestId();
    if (requestId == _curRequestIdGetOrderItems)
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
                for (int i = 0; i < listData.count(); ++i)
                {
                    LazadaDataItemBillOrder *item = listData.at(i);
                    if (item)
                    {

                        LazadaDataItemBillOrder *dataOld = _hashDataOrderItems.value(item->OrderId(), NULL);
                        if (!dataOld)
                        {
                            dataOld = (LazadaDataItemBillOrder*)item->clone();
                            _hashDataOrderItems.insert(dataOld->OrderId(), dataOld);
                        }
                        else
                        {
                            item->cloneData(dataOld);
                        }

                        delete item;
                        item = NULL;
                    }

                }

                IObjRequestListener *pObjListener = _hashOjectListener.value(requestId, NULL);
                if (pObjListener)
                {
                    ResponseResult *response = new ResponseResult(a_pRequest->getRequestType(),
                                                                  a_pRequest->getErrorMessage());
                    pObjListener->OnRequestCompleted(response);
                }
            }
            _hashOjectListener.remove(requestId);
            break;
        }

        default:
            break;
        }
        _curRequestIdGetOrderItems = -1;
    }
}

void LazadaHandler::OnApiRequestComplete(IApiRequest *a_pRequest)
{
    qDebug() << "COMPLETE";
    if (!a_pRequest) return;
    int requestType = a_pRequest->getRequestType();
    switch (requestType)
    {
    case LazadaApiCommandDefined::LAZADA_REQ_GET_ORDERS:
    {
        handleResponseApiListOrder(a_pRequest);
        break;
    }

    case LazadaApiCommandDefined::LAZADA_REQ_GET_ORDER:
    {
        handleResponseApiOrder(a_pRequest);
        break;
    }

    case LazadaApiCommandDefined::LAZADA_REQ_GET_ORDER_ITEMS:
    {
        handleResponseApiOrderItems(a_pRequest);
        break;
    }

    default:
        break;
    }
}

void LazadaHandler::OnApiRequestError(IApiRequest *a_pRequest)
{
    qDebug() << "ERROR ";
    if (!a_pRequest) return;
    int requestType = a_pRequest->getRequestType();
    switch (requestType)
    {
    case LazadaApiCommandDefined::LAZADA_REQ_GET_ORDERS:
    {
        handleResponseApiListOrder(a_pRequest);
        break;
    }

    case LazadaApiCommandDefined::LAZADA_REQ_GET_ORDER:
    {
        handleResponseApiOrder(a_pRequest);
        break;
    }

    case LazadaApiCommandDefined::LAZADA_REQ_GET_ORDER_ITEMS:
    {
        handleResponseApiOrderItems(a_pRequest);
        break;
    }

    default:
        break;
    }
}
