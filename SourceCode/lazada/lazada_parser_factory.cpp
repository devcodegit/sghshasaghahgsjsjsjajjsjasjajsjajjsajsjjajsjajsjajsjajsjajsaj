#include "lazada_parser_factory.h"
#include "dataitem/lazada_data_item_list_order.h"
#include "dataitem/lazada_data_item_order.h"
#include "dataitem/lazada_data_item_order_items.h"

using namespace Core::Lazada::Parser;
using namespace Core::DataItem;

AbstractDataItem *LazadaParserFactory::lazadaCreateParserListOrder()
{
    LazadaDataItemListOrder *dataItem = new LazadaDataItemListOrder();
    return dataItem;
}

AbstractDataItem *LazadaParserFactory::lazadaCreateParserOrder()
{
    LazadaDataItemOrder *dataItem = new LazadaDataItemOrder();
    return dataItem;
}

AbstractDataItem *LazadaParserFactory::lazadaCreateParserOrderItems()
{
    LazadaDataItemOrderItems *dataItem = new LazadaDataItemOrderItems();
    return dataItem;
}
