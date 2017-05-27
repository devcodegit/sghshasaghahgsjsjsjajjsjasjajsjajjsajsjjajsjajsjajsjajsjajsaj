#ifndef LAZADA_DATA_ITEM_LIST_ORDER_H
#define LAZADA_DATA_ITEM_LIST_ORDER_H

#include "../../core/dataitem/abstract_data_item.h"
#include <QList>

namespace Core { namespace DataItem {

    class LazadaDataItemOrder;

    class LazadaDataItemListOrder : public AbstractDataItem
    {
    public:
        LazadaDataItemListOrder();

        virtual AbstractDataItem* clone() const;
        virtual void parseItemData(Value& aJsonObject);

        QList<LazadaDataItemOrder *> getListData();

    private:
        QList<LazadaDataItemOrder *> _listData;
    };

}}

#endif // LAZADA_DATA_ITEM_LIST_ORDER_H
