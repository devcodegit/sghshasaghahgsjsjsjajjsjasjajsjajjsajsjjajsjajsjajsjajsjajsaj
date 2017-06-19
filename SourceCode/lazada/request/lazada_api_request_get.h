#ifndef LAZADA_API_REQUEST_H
#define LAZADA_API_REQUEST_H

#include "../../core/request/apirequest_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestGET : public ApiRequestGET
    {
    public:
        LazadaApiRequestGET();

        virtual void generateParams(QHash<QString, QString>* a_pParams) = 0;
        virtual QString generateSignature(QString data, QString key);

    protected:
        virtual QString prepareGETParams(QHash<QString, QString> *a_pParams);
        virtual void parseData(const QByteArray& a_ResponseData);
        virtual int parseErrorCode(Value& aJsonObject);

    public:
        QString getTimestamp();
        QString convertTimeToStringISO8601(const qint64 time);

    private:
        void ParseDataError(Value &aJsonObject);
        void ParseDataSuccess(Value &aJsonObject);
        void ParseHead(Value &aJsonObject);
        void ParseBody(Value &aJsonObject);

    protected:
        QString _strRequestAction;
        QString _strResponseType;
        QString _strRequestId;
        QString _strTimeStamp;
        int _iTotalCount = 0;
    };

}}
#endif // LAZADA_API_REQUEST_H
