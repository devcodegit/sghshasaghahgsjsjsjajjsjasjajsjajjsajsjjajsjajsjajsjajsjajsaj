#include "lazada_api_request_get_document.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestGetDocument::LazadaApiRequestGetDocument(IApiRequestListener *a_pListener, QList<uint32_t> OrderItemIds, const QString &DocumentType)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;
    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_GET_DOCUMENT;
    m_OrderItemIds = OrderItemIds;
    m_DocumentType = DocumentType;
}

void LazadaApiRequestGetDocument::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_GET_DOCUMENT);
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);
    a_pParams->insert(QString("DocumentType"), m_DocumentType);
    a_pParams->insert(QString("OrderItemIds"),convertListToString(m_OrderItemIds));
}
