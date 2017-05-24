#include "lazada_handler.h"
#include "lazada_request_api_factory.h"
#include "lazada_parser_factory.h"
#include "../core/request/apirequest_worker.h"
#include "../core/request/apirequest.h"

using namespace Core::Request;
using namespace Core::Lazada::Request;
using namespace Core::Lazada::Parser;

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

void LazadaHandler::requestListOrder()
{
    qDebug() << "LazadaHandler::requestListOrder";
    auto request = LazadaRequestApiFactory::lazadaCreateApiRequestListOrder(this);
    request->setParser(LazadaParserFactory::lazadaCreateParserListOrder());
    ApiRequestWorker::instance()->AddRequest(request);
}

void LazadaHandler::requestItemOrder()
{

}

void LazadaHandler::handleResponseApiListOrder()
{

}

void LazadaHandler::handleResponseApiItemOrder()
{

}

void LazadaHandler::OnApiRequestComplete(IApiRequest *a_pRequest)
{

}

void LazadaHandler::OnApiRequestError(IApiRequest *a_pRequest)
{

}
