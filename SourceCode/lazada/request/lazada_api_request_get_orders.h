#ifndef LAZADA_API_REQUEST_LIST_ORDER_H
#define LAZADA_API_REQUEST_LIST_ORDER_H

#include "lazada_api_request_get.h"

namespace Core { namespace Request {

/**
  * Get list order
  */

    class LazadaApiRequestGetOrders : public LazadaApiRequestGET
    {
    public:
        LazadaApiRequestGetOrders(IApiRequestListener *a_pListener,
                                  const int Limit = -1,
                                  const int Offset = -1,
                                  const qint64 CreatedAfter = -1,
                                  const qint64 CreatedBefore = -1,
                                  const qint64 UpdatedAfter = -1,
                                  const qint64 UpdatedBefore = -1,
                                  const QString &Status = "",
                                  const QString &SortBy = "",
                                  const QString &SortDirection = "");
        virtual void generateParams(QHash<QString, QString>* a_pParams);

    private:

        /**
          @Status:
             * pending
             * canceled
             * ready_to_ship
             * delivered
             * returned
             * shipped
             * failed
        */
        QString m_Status;

        /**
          @ SortBy:
            *  created_at
            *  updated_at
        */
        QString m_SortBy;

        /**
          @ SortDirection:
            * ASC.
            * DESC.
        */
        QString m_SortDirection;

        qint64 m_CreatedAfter = -1;
        qint64 m_CreatedBefore = -1;
        qint64 m_UpdatedAfter = -1;
        qint64 m_UpdatedBefore = -1;

        int m_Limit = -1;
        int m_Offset = -1;
    };

}}

#endif // LAZADA_API_REQUEST_LIST_ORDER_H
