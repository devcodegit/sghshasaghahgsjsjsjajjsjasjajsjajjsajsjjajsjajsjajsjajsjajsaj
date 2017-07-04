#ifndef LAZADA_REQUEST_H
#define LAZADA_REQUEST_H

#include <QMutex>
#include <QHash>

#include "../core/request/i_api_request_listener.h"
#include "../global.h"
using namespace Core::Request;

namespace Core { namespace Listener {
    class ObjectListenter;
}}
using namespace Core::Listener;

namespace Lazada { namespace DataModel {
    class DataOrderItem;
    class DataOrder;
}}
using namespace Lazada::DataModel;

namespace Lazada { namespace Request {

    class LazadaRequest : public IApiRequestListener
    {
        LazadaRequest();
        static LazadaRequest *Instance;
        static QMutex mutexIns;
    public:
        static LazadaRequest *instance();

        void requestGetOrders(ObjectListenter *pListener, const int page = 0, const int limit = -1);
        void requestGetOrderItems(ObjectListenter *pListener, const uint32_t orderId);
        void requestSetStatusToPackedByMarketplace(ObjectListenter *pListener, QList<uint32_t> listOrderItems);
        void requestSetStatusToReadyToShip(ObjectListenter *pListener, QList<uint32_t> listOrderItems);
        void requestGetDocument(ObjectListenter *pListener, QList<uint32_t> listOrderItems, const QString &DocumentType);

    protected:
        virtual void OnApiRequestComplete(IApiRequest* a_pRequest);
        virtual void OnApiRequestError(IApiRequest* a_pRequest);

    private:
        void handleResponseApiListOrder(IApiRequest *a_pRequest);
        void handleResponseApiOrderItems(IApiRequest *a_pRequest);
        void handleResponseApiGetDocument(IApiRequest *a_pRequest);
        void handleResponseApiSetStatusToPackedByMarketplace(IApiRequest *a_pRequest);

    private:
        ObjectListenter *_pCurListenerGetOrder = 0;
        ObjectListenter *_pCurListenerGetOrderItems = 0;
        QHash<int, ObjectListenter *> _hashListenerGetDocument;
        QHash<int, uint32_t> _hashIdRequestSetStatusToPackedByMarketplace;

        int _iCurRequestIdGetListOrder = -1;
        int _iCurRequestIdGetOrderItems = -1;
    };

}}


#endif // LAZADA_REQUEST_H
