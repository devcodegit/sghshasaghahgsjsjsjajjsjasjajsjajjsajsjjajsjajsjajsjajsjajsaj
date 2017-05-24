#ifndef APIREQUESTGET_H
#define APIREQUESTGET_H

#include "apirequest.h"

namespace Core { namespace Request {

    class ApiRequestGET : public ApiRequest
    {
    public:
        ApiRequestGET();

        virtual void generateParams(QHash<QString, QString>* a_pParams) = 0;
        virtual QString generateSignature(QString data, QString key) = 0;

    private:
        virtual QString generatePostData() { return NULL; }
        virtual QByteArray generateMultipartData() { return NULL; }
    };

}}
#endif // APIREQUESTGET_H
