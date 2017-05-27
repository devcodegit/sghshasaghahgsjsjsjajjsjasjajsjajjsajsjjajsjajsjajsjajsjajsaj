#ifndef LAZADA_HANDLER_H
#define LAZADA_HANDLER_H

#include "../core/request/i_api_request_listener.h"

#include <QMutex>
#include <QHash>

namespace Core { namespace DataItem {
    class LazadaDataItemOrder;
    class LazadaDataItemBillOrder;
}}

using namespace Core::DataItem;
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

        QList<LazadaDataItemOrder *> getAllDataOrders(IObjRequestListener *pListener = NULL);
        LazadaDataItemOrder * getDataOrder(const qint64 orderId, IObjRequestListener *pListener = NULL);
        LazadaDataItemBillOrder *getBillOrder(const qint64 orderId, IObjRequestListener *pListener = NULL);

    protected:
        virtual void OnApiRequestComplete(IApiRequest* a_pRequest);
        virtual void OnApiRequestError(IApiRequest* a_pRequest);

    private:
        void requestListOrder(IObjRequestListener *pListener);
        void requestOrder(int orderId, IObjRequestListener *pListener);
        void requestOrderItems(int orderId, IObjRequestListener *pListener);

        void handleResponseApiListOrder(IApiRequest *a_pRequest);
        void handleResponseApiOrder(IApiRequest *a_pRequest);
        void handleResponseApiOrderItems(IApiRequest *a_pRequest);

    private:
        QHash<int, IObjRequestListener*> _hashOjectListener;
        QHash<qint64, LazadaDataItemOrder *> _hashDataOrders;
        QHash<qint64, LazadaDataItemBillOrder *> _hashDataOrderItems;

        QList<LazadaDataItemOrder *> _listDataOrders;
        QList<LazadaDataItemBillOrder *> _listDataOrderItems;

        int _curRequestIdGetListOrder = -1;
        int _curRequestIdGetOrder = -1;
        int _curRequestIdGetOrderItems = -1;

        qint64 _timeRequestAllListOrder = 0;
        qint64 _timeRequestAllOrderItems = 0;
    };

}
}


#endif // LAZADA_HANDLER_H
