#ifndef LAZADA_API_REQUEST_GET_DOCUMENT_H
#define LAZADA_API_REQUEST_GET_DOCUMENT_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestGetDocument : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestGetDocument(IApiRequestListener *a_pListener, QList<uint32_t> OrderItemIds, const QString &DocumentType);
        virtual void generateParams(QHash<QString, QString>* a_pParams);

    private:
        QList<uint32_t> m_OrderItemIds;
        QString m_DocumentType;
    };

}}
#endif // LAZADA_API_REQUEST_GET_DOCUMENT_H
