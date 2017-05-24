#include "lazada_data_item_list_order.h"
#include "lazada_data_item_order_item.h"
#include "../../core/jsonutil/json_utils.h"
#include "../../core/jsonutil/json_exception.h"
#include <QDebug>

using namespace Core::DataItem;
using namespace Core::Json;

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
    Value &aJsonArray = JsonUtils::getJsonArray(aJsonObject, "Orders");
    if (!aJsonArray.IsNull())
    {
        for (int i = 0; i < (int)aJsonArray.Size(); i++)
        {
            try
            {
                Value &itemValue = JsonUtils::tryGetJsonObject(aJsonArray, i);
                if (!itemValue.IsNull())
                {
                    LazadaDataItemOrderItem *itemData = new LazadaDataItemOrderItem();
                    itemData->parseItemData(itemValue);
                    _listData.append(itemData);
                }
            }
            catch (JsonException ex)
            {
                qDebug() << "ERROR GetFullListFriendSuggestionDataItem::parseDataJson: " << ex.what();
            }

        }
        qDebug() << "FINISH";
    }
}

QList<LazadaDataItemOrderItem *> LazadaDataItemListOrder::getListData()
{
    return _listData;
}
