#include "lazada_handler.h"
#include "lazada_request_api_factory.h"
#include "lazada_parser_factory.h"
#include "../core/request/apirequest_worker.h"
#include "../core/request/apirequest.h"
#include "../lazada/lazada_api_command_defined.h"
#include "../lazada/request/lazada_api_request_list_order.h"
#include "../lazada/request/lazada_api_request_order.h"
#include "../lazada/request/lazada_api_request_order_items.h"
#include "../lazada/dataitem/lazada_data_item_list_order.h"
#include "../lazada/dataitem/lazada_data_item_order.h"
#include "../lazada/dataitem/lazada_data_item_order_items.h"
#include "../lazada/dataitem/lazada_data_item_bill_order.h"

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
            LazadaApiRequestListOrder *requestListOrder = (LazadaApiRequestListOrder*)a_pRequest;
            LazadaDataItemListOrder *dataItem = (LazadaDataItemListOrder*)a_pRequest->getDataItem();
            if (dataItem)
            {
                QList<LazadaDataItemOrder *> listData = dataItem->getListData();
                for (int i = 0; i < listData.count(); ++i)
                {
                    LazadaDataItemOrder *item = listData.at(i);
                    if (item)
                    {

                        //KhaTH todo:
                        /**
                         * @ clone data từ datajson Push data vao model mong muon.
                        */


                        //------------------

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
            LazadaApiRequestOrder *requestListOrder = (LazadaApiRequestOrder*)a_pRequest;
            LazadaDataItemOrder *dataItem = (LazadaDataItemOrder*)a_pRequest->getDataItem();
            if (dataItem)
            {

                //KhaTH todo:
                /**
                 * @ clone data từ datajson Push data vao model mong muon.
                */


                //------------------

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
            LazadaApiRequestOrderItems *requestListOrder = (LazadaApiRequestOrderItems*)a_pRequest;
            LazadaDataItemOrderItems *dataItem = (LazadaDataItemOrderItems*)a_pRequest->getDataItem();
            if (dataItem)
            {
                QList<LazadaDataItemBillOrder *> listData = dataItem->getListData();
                for (int i = 0; i < listData.count(); ++i)
                {
                    LazadaDataItemBillOrder *item = listData.at(i);
                    if (item)
                    {

                        //KhaTH todo:
                        /**
                         * @ clone data từ datajson Push data vao model mong muon.
                        */


                        //------------------

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
    case LazadaApiCommandDefined::LAZADA_REQ_GET_LIST_ORDER:
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
    case LazadaApiCommandDefined::LAZADA_REQ_GET_LIST_ORDER:
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
