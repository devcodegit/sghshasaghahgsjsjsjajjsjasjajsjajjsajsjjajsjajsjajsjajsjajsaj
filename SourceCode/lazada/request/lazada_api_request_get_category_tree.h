#ifndef LAZADA_API_REQUEST_GET_CATEGORY_TREE_H
#define LAZADA_API_REQUEST_GET_CATEGORY_TREE_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestGetCategoryTree : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestGetCategoryTree(IApiRequestListener *a_pListener);
        virtual void generateParams(QHash<QString, QString>* a_pParams);
    };

}}

#endif // LAZADA_API_REQUEST_GET_CATEGORY_TREE_H
