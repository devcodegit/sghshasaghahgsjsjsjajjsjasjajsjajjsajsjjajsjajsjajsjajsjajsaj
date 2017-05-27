#ifndef LAZADA_PARSER_FACTORY_H
#define LAZADA_PARSER_FACTORY_H

#include "../core/dataitem/abstract_data_item.h"

using namespace Core::DataItem;

namespace Core { namespace Lazada { namespace Parser {

    class LazadaParserFactory
    {
    public:
        static AbstractDataItem *lazadaCreateParserListOrder();
        static AbstractDataItem *lazadaCreateParserOrder();
        static AbstractDataItem *lazadaCreateParserOrderItems();
    };

}}}

#endif // LAZADA_PARSER_FACTORY_H
