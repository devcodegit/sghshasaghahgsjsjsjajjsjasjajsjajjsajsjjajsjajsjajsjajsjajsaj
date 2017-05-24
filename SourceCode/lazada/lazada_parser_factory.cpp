#include "lazada_parser_factory.h"
#include "dataitem/lazada_data_item_list_order.h"

using namespace Core::Lazada::Parser;
using namespace Core::DataItem;

AbstractDataItem *LazadaParserFactory::lazadaCreateParserListOrder()
{
    LazadaDataItemListOrder *dataItem = new LazadaDataItemListOrder();
    return dataItem;
}
