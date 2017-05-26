#include "lazada_handler.h"
#include "lazada_request_api_factory.h"
#include "lazada_parser_factory.h"
#include "../core/request/apirequest_worker.h"
#include "../core/request/apirequest.h"
#include "../lazada/lazada_api_command_defined.h"
#include "../lazada/request/lazada_api_request_list_order.h"
#include "../lazada/dataitem/lazada_data_item_list_order.h"
#include "../lazada/dataitem/lazada_data_item_order_item.h"

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

void LazadaHandler::requestItemOrder()
{

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
                QList<LazadaDataItemOrderItem *> listData = dataItem->getListData();
                for (int i = 0; i < listData.count(); ++i)
                {
                    LazadaDataItemOrderItem *item = listData.at(i);
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

    }
}

void LazadaHandler::handleResponseApiItemOrder()
{

}

void LazadaHandler::OnApiRequestComplete(IApiRequest *a_pRequest)
{
    if (!a_pRequest) return;
    int requestType = a_pRequest->getRequestType();
    switch (requestType)
    {
    case LazadaApiCommandDefined::LAZADA_REQ_GET_LIST_ORDER:
        handleResponseApiListOrder(a_pRequest);
        break;
    default:
        break;
    }
}

void LazadaHandler::OnApiRequestError(IApiRequest *a_pRequest)
{

}
