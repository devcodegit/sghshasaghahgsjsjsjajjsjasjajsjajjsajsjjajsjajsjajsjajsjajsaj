#include "lazada_api_request_get_shipment_providers.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestGetShipmentProviders::LazadaApiRequestGetShipmentProviders(IApiRequestListener *a_pListener)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;
    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_GET_SHIPMENT_PROVIDERS;
}

void LazadaApiRequestGetShipmentProviders::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_GET_SHIPMENT_PROVIDERS);
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);
}
