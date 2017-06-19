#include "lazada_api_request_search_spus.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestSearchSPUs::LazadaApiRequestSearchSPUs(IApiRequestListener *a_pListener, const QString &CategoryId, const QString &Search, const int Offset, const int Limit)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;

    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_SEARCH_SPUs;
    m_CategoryId = CategoryId;
    m_Search = Search;
    m_Offset = Offset;
    m_Limit = Limit;
}

void LazadaApiRequestSearchSPUs::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_SEARCH_SPUs);
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);
    a_pParams->insert(QString("CategoryId"), m_CategoryId);
    a_pParams->insert(QString("Search"), m_Search);
    a_pParams->insert(QString("Offset"), QString::number(m_Offset));
    a_pParams->insert(QString("Limit"), QString::number(m_Limit));
}
