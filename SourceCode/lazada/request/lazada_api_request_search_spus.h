#ifndef LAZADA_API_REQUEST_SEARCH_SPUS_H
#define LAZADA_API_REQUEST_SEARCH_SPUS_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestSearchSPUs : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestSearchSPUs(IApiRequestListener *a_pListener,
                                   const QString &CategoryId,
                                   const QString &Search,
                                   const int Offset,
                                   const int Limit);
        virtual void generateParams(QHash<QString, QString>* a_pParams);

    private:
        QString m_CategoryId;
        QString m_Search;
        int m_Offset = 0;
        int m_Limit = 0;
    };

}}

#endif // LAZADA_API_REQUEST_SEARCH_SPUS_H
