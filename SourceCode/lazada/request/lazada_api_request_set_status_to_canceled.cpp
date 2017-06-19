#include "lazada_api_request_set_status_to_canceled.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestSetStatusToCanceled::LazadaApiRequestSetStatusToCanceled(IApiRequestListener *a_pListener, const qint64 OrderItemId, const QString &Reason, const QString &ReasonDetail)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;

    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_SET_STATUS_TO_CANCELED;
    m_OrderItemId = OrderItemId;
    m_Reason = Reason;
    m_ReasonDetail = ReasonDetail;
}

void LazadaApiRequestSetStatusToCanceled::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_SET_STATUS_TO_CANCELED);
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);
    a_pParams->insert(QString("OrderItemId"), QString::number(m_OrderItemId));
    a_pParams->insert(QString("Reason"), m_Reason);
    a_pParams->insert(QString("ReasonDetail"), m_ReasonDetail);
}
