#ifndef LAZADA_API_REQUEST_GET_BRANDS_H
#define LAZADA_API_REQUEST_GET_BRANDS_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestGetBrands : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestGetBrands(IApiRequestListener *a_pListener, const int Limit, const int Offset);
        virtual void generateParams(QHash<QString, QString>* a_pParams);

    private:
        int m_Limit = -1;
        int m_Offset = -1;
    };

}}

#endif // LAZADA_API_REQUEST_GET_BRANDS_H
