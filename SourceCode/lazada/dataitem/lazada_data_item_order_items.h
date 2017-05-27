#ifndef LAZADA_DATA_ITEM_ORDER_ITEMS_H
#define LAZADA_DATA_ITEM_ORDER_ITEMS_H

#include <QList>

#include "../../core/dataitem/abstract_data_item.h"

namespace Core { namespace DataItem {

    class LazadaDataItemBillOrder;

    class LazadaDataItemOrderItems : public AbstractDataItem
    {
    public:
        LazadaDataItemOrderItems();

        virtual AbstractDataItem* clone() const;
        virtual void parseItemData(Value& aJsonObject);

        QList<LazadaDataItemBillOrder *> getListData();

    private:
        QList<LazadaDataItemBillOrder *> _listData;
    };

}}
#endif // LAZADA_DATA_ITEM_ORDER_ITEMS_H
