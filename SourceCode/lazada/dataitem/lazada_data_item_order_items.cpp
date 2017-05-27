#include "lazada_data_item_order_items.h"
#include "lazada_data_item_bill_order.h"
#include "../../core/jsonutil/json_utils.h"
#include "../../core/jsonutil/json_exception.h"
#include <QDebug>

using namespace Core::DataItem;
using namespace Core::Json;

LazadaDataItemOrderItems::LazadaDataItemOrderItems()
{

}

AbstractDataItem *LazadaDataItemOrderItems::clone() const
{
    return new LazadaDataItemOrderItems(*this);
}

void LazadaDataItemOrderItems::parseItemData(Value &aJsonObject)
{
    qDebug() << "LazadaDataItemOrder::parseItemData";
    Value &aJsonArray = JsonUtils::getJsonArray(aJsonObject, "OrderItems");
    if (!aJsonArray.IsNull())
    {
        for (int i = 0; i < (int)aJsonArray.Size(); i++)
        {
            try
            {
                Value &itemValue = JsonUtils::tryGetJsonObject(aJsonArray, i);
                if (!itemValue.IsNull())
                {
                    LazadaDataItemBillOrder *itemData = new LazadaDataItemBillOrder();
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

QList<LazadaDataItemBillOrder *> LazadaDataItemOrderItems::getListData()
{
    return _listData;
}
