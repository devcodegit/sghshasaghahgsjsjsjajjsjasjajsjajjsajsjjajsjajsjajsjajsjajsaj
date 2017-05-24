#ifndef LAZADA_HANDLER_H
#define LAZADA_HANDLER_H

#include "../core/request/i_api_request_listener.h"
#include <QMutex>

using namespace Core::Request;

class LazadaHandler : public IApiRequestListener
{
    static LazadaHandler *Instance;
    static QMutex mutexIns;
    LazadaHandler();

public:
    static LazadaHandler *instance();

    void requestListOrder();
    void requestItemOrder();

    void handleResponseApiListOrder();
    void handleResponseApiItemOrder();

protected:
    virtual void OnApiRequestComplete(IApiRequest* a_pRequest);
    virtual void OnApiRequestError(IApiRequest* a_pRequest);
};

#endif // LAZADA_HANDLER_H
