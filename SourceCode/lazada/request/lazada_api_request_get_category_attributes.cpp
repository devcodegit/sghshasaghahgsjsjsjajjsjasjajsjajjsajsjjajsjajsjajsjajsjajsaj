#include "lazada_api_request_get_category_attributes.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestGetCategoryAttributes::LazadaApiRequestGetCategoryAttributes(IApiRequestListener *a_pListener, const int PrimaryCategory)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;
    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_GET_CATEGORY_ATTRIBUTES;
    m_PrimaryCategory = PrimaryCategory;
}

void LazadaApiRequestGetCategoryAttributes::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_GET_CATEGORY_ATTRIBUTES);
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);
    a_pParams->insert(QString("PrimaryCategory"), QString::number(m_PrimaryCategory));
}
