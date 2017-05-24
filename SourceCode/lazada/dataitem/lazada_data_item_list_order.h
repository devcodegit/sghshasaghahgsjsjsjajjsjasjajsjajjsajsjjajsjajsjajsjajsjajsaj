#ifndef LAZADA_DATA_ITEM_LIST_ORDER_H
#define LAZADA_DATA_ITEM_LIST_ORDER_H

#include "../../core/dataitem/abstract_data_item.h"

namespace Core { namespace DataItem {

    class LazadaDataItemListOrder : public AbstractDataItem
    {
    public:
        LazadaDataItemListOrder();

        virtual AbstractDataItem* clone() const;
        virtual void parseItemData(Value& aJsonObject);
    };

}}

#endif // LAZADA_DATA_ITEM_LIST_ORDER_H
