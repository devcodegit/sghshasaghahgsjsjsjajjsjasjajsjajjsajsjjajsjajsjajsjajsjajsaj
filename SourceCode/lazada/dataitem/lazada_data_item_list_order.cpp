#include "lazada_data_item_list_order.h"
#include <QDebug>

using namespace Core::DataItem;

LazadaDataItemListOrder::LazadaDataItemListOrder()
{

}

AbstractDataItem *LazadaDataItemListOrder::clone() const
{
    return new LazadaDataItemListOrder(*this);
}

void LazadaDataItemListOrder::parseItemData(Value &aJsonObject)
{
    qDebug() << "LazadaDataItemListOrder::parseItemData";
}
