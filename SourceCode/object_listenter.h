#ifndef OBJECT_LISTENTER_H
#define OBJECT_LISTENTER_H

#include <QString>

namespace Core { namespace Listener {

    class ResultListener
    {
    public:
        ResultListener(const int requestType, const int errorCode, const QString &errorMsg, const QString &data = "")
        {
            _requestType = requestType;
            _errorCode = errorCode;
            _errorMsg = errorMsg;
            _data = data;
        }

        int getRequestType() {return _requestType;}
        int getErrorCode() {return _errorCode;}
        QString getErrorMessage() {return _errorMsg;}
        QString getData() {return _data;}

    private:
        int _requestType;
        int _errorCode;
        QString _errorMsg;
        QString _data;
    };

    class ObjectListenter
    {
    public:
        ~ObjectListenter(){}

        virtual void OnRequestCompleted(ResultListener *result) = 0;
        virtual void OnRequestFailed(ResultListener *result) = 0;
    };

}}
#endif // OBJECT_LISTENTER_H
