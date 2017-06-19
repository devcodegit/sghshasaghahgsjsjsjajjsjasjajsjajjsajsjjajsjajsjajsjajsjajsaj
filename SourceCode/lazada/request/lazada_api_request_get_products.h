#ifndef LAZADA_API_REQUEST_GET_PRODUCTS_H
#define LAZADA_API_REQUEST_GET_PRODUCTS_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

    class LazadaApiRequestGetProducts : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestGetProducts(IApiRequestListener *a_pListener,
                                    QStringList SkuSellerList,
                                    const qint64 CreatedAfter = 0,
                                    const qint64 CreatedBefore = 0,
                                    const qint64 UpdatedAfter = 0,
                                    const qint64 UpdatedBefore = 0,
                                    const QString &Search = "",
                                    const QString &Filter = "",
                                    const int Limit = -1,
                                    const int Option = -1,
                                    const int Offset = -1);
        virtual void generateParams(QHash<QString, QString>* a_pParams);

    private:
        QStringList m_SkuSellerList;

        QString m_Search;
        QString m_Filter;

        qint64 m_CreatedAfter = 0;
        qint64 m_CreatedBefore = 0;
        qint64 m_UpdatedAfter = 0;
        qint64 m_UpdatedBefore = 0;

        int m_Limit = -1;
        int m_Option = -1;
        int m_Offset = -1;
    };

}}

#endif // LAZADA_API_REQUEST_GET_PRODUCTS_H
