#ifndef LAZADA_HANDLER_H
#define LAZADA_HANDLER_H

#include "../core/request/i_api_request_listener.h"
#include <QMutex>
#include <QHash>

using namespace Core::Request;

namespace Lazada { namespace Controls {

    class ResponseResult
    {
    public:
        ResponseResult(int requestType, const QString strErrorMsg = "", const qint64 userIdResponse = -1)
        {
            _typeRequest = requestType;
            _strErrorMsg = strErrorMsg;
            _userIdResponse = userIdResponse;
        }
        ~ResponseResult(){}

        int getRequestType() const {return _typeRequest;}
        QString getErrorMsg() const {return _strErrorMsg;}
        qint64 getUserIdResponse() const {return _userIdResponse;}

    private:
        int _typeRequest;
        QString _strErrorMsg;
        qint64 _userIdResponse;
    };

    class IObjRequestListener
    {
    public:
        ~IObjRequestListener() {}

        virtual void OnRequestCompleted(ResponseResult *result) = 0;
        virtual void OnRequestFailed(ResponseResult *result) = 0;
    };

    class LazadaHandler : public IApiRequestListener
    {
        static LazadaHandler *Instance;
        static QMutex mutexIns;
        LazadaHandler();

    public:
        static LazadaHandler *instance();

        void requestListOrder(IObjRequestListener *pListener);
        void requestOrder(int orderId, IObjRequestListener *pListener);
        void requestOrderItems(int orderId, IObjRequestListener *pListener);

        void handleResponseApiListOrder(IApiRequest *a_pRequest);
        void handleResponseApiOrder(IApiRequest *a_pRequest);
        void handleResponseApiOrderItems(IApiRequest *a_pRequest);

    protected:
        virtual void OnApiRequestComplete(IApiRequest* a_pRequest);
        virtual void OnApiRequestError(IApiRequest* a_pRequest);

    private:
        QHash<int, IObjRequestListener*> _hashOjectListener;

        int _curRequestIdGetListOrder = -1;
        int _curRequestIdGetOrder = -1;
        int _curRequestIdGetOrderItems = -1;
    };

}
}


#endif // LAZADA_HANDLER_H
