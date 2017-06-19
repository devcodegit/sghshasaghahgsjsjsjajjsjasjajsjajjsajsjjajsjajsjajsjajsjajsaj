#include "lazada_api_request_update_price_quantity.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestUpdatePriceQuantity::LazadaApiRequestUpdatePriceQuantity(IApiRequestListener *a_pListener)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;
    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_UPDATE_PRICE_QUANTITY;
}

void LazadaApiRequestUpdatePriceQuantity::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_UPDATE_PRICE_QUANTITY);
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);
}
