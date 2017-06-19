#include "lazada_api_request_get_payout_status.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestGetPayoutStatus::LazadaApiRequestGetPayoutStatus(IApiRequestListener *a_pListener, const qint64 CreatedAfter)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;

    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_GET_PAYOUT_STATUS;
    m_CreatedAfter = CreatedAfter;
}

void LazadaApiRequestGetPayoutStatus::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_GET_PAYOUT_STATUS);
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);
//    a_pParams->insert(QString("CreatedAfter"), ) chua biet support
}
