#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QObject>

#include "iapi_request.h"
#include "i_api_finish_listener.h"
#include "i_api_request_listener.h"
#include "../network/http_connection.h"
#include "../jsonutil/json_utils.h"

namespace Core { namespace DataItem {
    class AbstractDataItem;
}}

using namespace Core::Network;
using namespace Core::DataItem;

namespace Core { namespace Request {

    class ApiRequest : public QObject, public IApiRequest
    {
        Q_OBJECT
    public:
        enum RequestPriority
        {
            CRITICAL,
            HIGH,
            NORMAL,
            LOW
        };

        explicit ApiRequest();
        virtual ~ApiRequest();

        void setParser(AbstractDataItem *parser);
        void setFinishListener(IApiFinishListener* aListener);
        void Handle(QNetworkAccessManager* a_pNetworkManager);
        void Start();

        RequestPriority getPriority();

        void cancelRequest();

    public:
        virtual void generateParams(QHash<QString, QString>* a_pParams) = 0;
        virtual QString generateSignature(QString data, QString key) = 0;
        virtual QString generatePostData() = 0;
        virtual QByteArray generateMultipartData() = 0;

    public:
        virtual int getRequestId();
        virtual int getErrorCode();
        virtual QString getErrorMessage();
        virtual int getRequestType();
        virtual AbstractDataItem *getDataItem();

    public:
        enum RequestMethod
        {
            GET,
            POST,
            MULTIPART
        };

    signals:

    public slots:
        void onHttpConnectionComplete();

    protected:
        virtual QString prepareGETParams(QHash<QString, QString>* a_pParams) = 0;
        virtual void parseData(const QByteArray& a_ResponseData) = 0;
        virtual int parseErrorCode(Value& aJsonObject) = 0;
        virtual void DoCompletedApiRequest() {}

    protected:
        QThread* m_pWorkerThread;
        HttpConnection *m_pHttpConnection;
        AbstractDataItem *m_pDataItem;
        IApiRequestListener* m_pApiRequestListener;
        IApiFinishListener* m_pFinishListener;
        AbstractDataItem *m_pParser;

        RequestPriority m_ePriority;
        RequestMethod m_eRequestMethod;

        QString m_sErrorMsg;
        QString m_sDomainUrl;

        bool m_isAutoDelete;

        int m_iRequestId;
        int m_iErrorCode;
        int m_iRequestType;
        int m_iTimeoutRequest;

    };

} // End namespace Request
} // End namespace Core

#endif // APIREQUEST_H
