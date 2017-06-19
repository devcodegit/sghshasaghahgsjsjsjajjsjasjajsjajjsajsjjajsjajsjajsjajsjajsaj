#include "lazada_api_request_get_brands.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestGetBrands::LazadaApiRequestGetBrands(IApiRequestListener *a_pListener, const int Limit, const int Offset)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;

    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_GET_BRANDS;
    m_Limit = Limit;
    m_Offset = Offset;
}

void LazadaApiRequestGetBrands::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_GET_BRANDS);
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);
    a_pParams->insert(QString("Limit"), QString::number(m_Limit));
    a_pParams->insert(QString("Offset"), QString::number(m_Offset));
}
