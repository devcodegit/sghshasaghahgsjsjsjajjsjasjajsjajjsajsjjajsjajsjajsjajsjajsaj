#ifndef LAZADA_API_COMMAND_DEFINED_H
#define LAZADA_API_COMMAND_DEFINED_H

#include <QString>

namespace Lazada { namespace Api {

    class LazadaApiCommandDefined
    {
    public:
        static const int LAZADA_REQ_GET_ORDERS                          =   1000;
        static const int LAZADA_REQ_GET_ORDER                           =   1001;
        static const int LAZADA_REQ_GET_ORDER_ITEMS                     =   1002;
        static const int LAZADA_REQ_SET_STATUS_TO_CANCELED              =   1003;
        static const int LAZADA_REQ_SET_STATUS_TO_PACKED_BY_MARKETPLACE =   1004;
        static const int LAZADA_REQ_SET_STATUS_TO_READY_TO_SHIP         =   1005;
        static const int LAZADA_REQ_SET_INVOICE_NUMBER                  =   1006;
        static const int LAZADA_REQ_GET_FAILURE_REASONS                 =   1007;
        static const int LAZADA_REQ_GET_DOCUMENT                        =   1008;
        static const int LAZADA_REQ_GET_SHIPMENT_PROVIDERS              =   1009;
        static const int LAZADA_REQ_GET_METRICS                         =   1010;
        static const int LAZADA_REQ_GET_PAYOUT_STATUS                   =   1011;
        static const int LAZADA_REQ_GET_STATISTICS                      =   1012;
        static const int LAZADA_REQ_SELLER_UPDATE                       =   1013;
        static const int LAZADA_REQ_USER_UPDATE                         =   1014;
        static const int LAZADA_REQ_GET_CATEGORY_ATTRIBUTES             =   1015;
        static const int LAZADA_REQ_GET_CATEGORY_TREE                   =   1016;
        static const int LAZADA_REQ_GET_BRANDS                          =   1017;
        static const int LAZADA_REQ_REMOVE_PRODUCT                      =   1018;
        static const int LAZADA_REQ_UPDATE_PRICE_QUANTITY               =   1019;
        static const int LAZADA_REQ_SET_IMAGE                           =   1020;
        static const int LAZADA_REQ_UPDATE_PRODUCT                      =   1021;
        static const int LAZADA_REQ_CREATE_PRODUCT                      =   1022;
        static const int LAZADA_REQ_MIGRATE_IMAGE                       =   1023;
        static const int LAZADA_REQ_UPLOAD_IMAGE                        =   1024;
        static const int LAZADA_REQ_SEARCH_SPUs                         =   1025;
        static const int LAZADA_REQ_GET_PRODUCT                         =   1026;

        // name action
        static const QString LAZADA_ACTION_GET_ORDERS;
        static const QString LAZADA_ACTION_GET_ORDER;
        static const QString LAZADA_ACTION_GET_ORDER_ITEMS;
        static const QString LAZADA_ACTION_SET_STATUS_TO_CANCELED;
        static const QString LAZADA_ACTION_SET_STATUS_TO_PACKED_BY_MARKETPLACE;
        static const QString LAZADA_ACTION_SET_STATUS_TO_READY_TO_SHIP ;
        static const QString LAZADA_ACTION_SET_INVOICE_NUMBER;
        static const QString LAZADA_ACTION_GET_FAILURE_REASONS;
        static const QString LAZADA_ACTION_GET_DOCUMENT;
        static const QString LAZADA_ACTION_GET_SHIPMENT_PROVIDERS;
        static const QString LAZADA_ACTION_GET_METRICS;
        static const QString LAZADA_ACTION_GET_PAYOUT_STATUS;
        static const QString LAZADA_ACTION_GET_STATISTICS;
        static const QString LAZADA_ACTION_SELLER_UPDATE;
        static const QString LAZADA_ACTION_USER_UPDATE;
        static const QString LAZADA_ACTION_GET_CATEGORY_ATTRIBUTES;
        static const QString LAZADA_ACTION_GET_CATEGORY_TREE;
        static const QString LAZADA_ACTION_GET_BRANDS;
        static const QString LAZADA_ACTION_REMOVE_PRODUCT;
        static const QString LAZADA_ACTION_UPDATE_PRICE_QUANTITY;
        static const QString LAZADA_ACTION_SET_IMAGE;
        static const QString LAZADA_ACTION_UPDATE_PRODUCT;
        static const QString LAZADA_ACTION_CREATE_PRODUCT;
        static const QString LAZADA_ACTION_MIGRATE_IMAGE;
        static const QString LAZADA_ACTION_UPLOAD_IMAGE;
        static const QString LAZADA_ACTION_SEARCH_SPUs;
        static const QString LAZADA_ACTION_GET_PRODUCT;
    };

}
}

#endif // LAZADA_API_COMMAND_DEFINED_H
