#ifndef ABSTRACT_DATA_ITEM_H
#define ABSTRACT_DATA_ITEM_H

#include "../jsonutil/json_utils.h"

namespace Core { namespace DataItem {

    class AbstractDataItem
    {
    public:
        AbstractDataItem();
        virtual ~AbstractDataItem();

        virtual AbstractDataItem* clone() const = 0;
        virtual void parseItemData(Value& aJsonObject) = 0;
    };

} // End namespace DataItem
} // End namespace Core

#endif // ABSTRACT_DATA_ITEM_H
