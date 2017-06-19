#ifndef LAZADA_API_REQUEST_GET_CATEGORY_ATTRIBUTES_H
#define LAZADA_API_REQUEST_GET_CATEGORY_ATTRIBUTES_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestGetCategoryAttributes : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestGetCategoryAttributes(IApiRequestListener *a_pListener, const int PrimaryCategory);
        virtual void generateParams(QHash<QString, QString>* a_pParams);

    private:
        int m_PrimaryCategory = -1;
    };

}}

#endif // LAZADA_API_REQUEST_GET_CATEGORY_ATTRIBUTES_H
