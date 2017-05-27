#ifndef LAZADA_API_COMMAND_DEFINED_H
#define LAZADA_API_COMMAND_DEFINED_H

#include <QString>

namespace Lazada { namespace Api {

    class LazadaApiCommandDefined
    {
    public:
        static const int LAZADA_REQ_GET_LIST_ORDER                      =   1000;
        static const int LAZADA_REQ_GET_ORDER                           =   1001;
        static const int LAZADA_REQ_GET_ORDER_ITEMS                     =   1002;


        // name action
        static const QString LAZADA_ACTION_GET_LIST_ORDER;
        static const QString LAZADA_ACTION_GET_ORDER;
        static const QString LAZADA_ACTION_GET_ORDER_ITEMS;

    };

}
}

#endif // LAZADA_API_COMMAND_DEFINED_H
