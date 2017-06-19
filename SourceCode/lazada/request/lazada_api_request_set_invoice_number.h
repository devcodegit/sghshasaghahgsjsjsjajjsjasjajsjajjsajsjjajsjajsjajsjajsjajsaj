#ifndef LAZADA_API_REQUEST_SET_INVOICE_NUMBER_H
#define LAZADA_API_REQUEST_SET_INVOICE_NUMBER_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestSetInvoiceNumber : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestSetInvoiceNumber(IApiRequestListener *a_pListener,
                                         const int OrderItemId,
                                         const QString &InvoiceNumber);
        virtual void generateParams(QHash<QString, QString>* a_pParams);

    private:
        int m_OrderItemId = -1;
        QString m_InvoiceNumber;
    };

}}
#endif // LAZADA_API_REQUEST_SET_INVOICE_NUMBER_H
