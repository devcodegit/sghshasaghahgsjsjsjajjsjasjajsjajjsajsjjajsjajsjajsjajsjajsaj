#ifndef INFO_API_REQUEST_H
#define INFO_API_REQUEST_H

#include <QString>

namespace Core {

namespace DataItem {
    class AbstractDataItem;
} // End DataItem

namespace Request {

    class IApiRequest
    {
    public:

        virtual int getRequestId() = 0;

        virtual int getErrorCode() = 0;

        virtual QString getErrorMessage() = 0;

        virtual int getRequestType() = 0;

        virtual Core::DataItem::AbstractDataItem* getDataItem() = 0;
    };

} // End Request
} // End Core

#endif // INFO_API_REQUEST_H
