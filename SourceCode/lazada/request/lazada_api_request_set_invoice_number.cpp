#include "lazada_api_request_set_invoice_number.h"
#include "../../core/service_map_manager.h"
#include "../lazada_api_command_defined.h"
#include "../lazada_define.h"

using namespace Core::Request;
using namespace Core::Service;
using namespace Lazada::Api;

LazadaApiRequestSetInvoiceNumber::LazadaApiRequestSetInvoiceNumber(IApiRequestListener *a_pListener, const int OrderItemId, const QString &InvoiceNumber)
{
    m_pApiRequestListener = a_pListener;
    m_sDomainUrl = DOMAIN_LAZADA;

    m_iRequestType = LazadaApiCommandDefined::LAZADA_REQ_SET_INVOICE_NUMBER;
    m_OrderItemId = OrderItemId;
    m_InvoiceNumber = InvoiceNumber;
}

void LazadaApiRequestSetInvoiceNumber::generateParams(QHash<QString, QString> *a_pParams)
{
    a_pParams->insert(QString("Action"), LazadaApiCommandDefined::LAZADA_ACTION_SET_INVOICE_NUMBER);
    a_pParams->insert(QString("Format"), FORMAT_RESPONSE);
    a_pParams->insert(QString("Timestamp"), getTimestamp());
    a_pParams->insert(QString("UserID"), USEID);
    a_pParams->insert(QString("Version"), VERSION);
    a_pParams->insert(QString("OrderItemId"), QString::number(m_OrderItemId));
    a_pParams->insert(QString("InvoiceNumber"), m_InvoiceNumber);
}
