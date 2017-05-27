#include "lazada_data_item_order.h"
#include "../../core/jsonutil/json_utils.h"
#include "../../core/jsonutil/json_exception.h"
#include <QDebug>

using namespace Core::Json;
using namespace Core::DataItem;

LazadaDataItemOrder::LazadaDataItemOrder()
{

}

AbstractDataItem *LazadaDataItemOrder::clone() const
{
    return new LazadaDataItemOrder(*this);
}

void LazadaDataItemOrder::parseItemData(Value &aJsonObject)
{
    if (!aJsonObject.IsNull())
    {
        try
        {
            m_OrderId = JsonUtils::tryGetLong(aJsonObject, "OrderId", -1);
            m_CustomerFirstName = JsonUtils::tryGetString(aJsonObject, "CustomerFirstName", "");
            m_CustomerLastName = JsonUtils::tryGetString(aJsonObject, "CustomerLastName", "");
            m_OrderNumber = JsonUtils::tryGetLong(aJsonObject, "OrderNumber", -1);
            m_PaymentMethod = JsonUtils::tryGetString(aJsonObject, "PaymentMethod", "");
            m_Remarks = JsonUtils::tryGetString(aJsonObject, "Remarks", "");
            m_DeliveryInfo = JsonUtils::tryGetString(aJsonObject, "DeliveryInfo", "");
            m_Price = JsonUtils::tryGetString(aJsonObject, "Price", "");
            m_GiftOption = JsonUtils::tryGetBool(aJsonObject, "GiftOption", false);
            m_GiftMessage = JsonUtils::tryGetString(aJsonObject, "GiftMessage", "");
            m_VoucherCode = JsonUtils::tryGetString(aJsonObject, "VoucherCode", "");
            m_CreatedAt = JsonUtils::tryGetString(aJsonObject, "CreatedAt", "");
            m_UpdatedAt = JsonUtils::tryGetString(aJsonObject, "UpdatedAt", "");
            m_NationalRegistrationNumber = JsonUtils::tryGetString(aJsonObject, "NationalRegistrationNumber", "");
            m_ItemsCount = JsonUtils::tryGetInt(aJsonObject, "ItemsCount", 0);
            m_PromisedShippingTimes = JsonUtils::tryGetString(aJsonObject, "PromisedShippingTimes", "");
            m_ExtraAttributes = JsonUtils::tryGetString(aJsonObject, "ExtraAttributes", "");
            m_Voucher = JsonUtils::tryGetInt(aJsonObject, "Voucher", 0);
            m_ShippingFee = JsonUtils::tryGetInt(aJsonObject, "ShippingFee", 0);

            Value &AddressShippingValue = JsonUtils::getJsonObject(aJsonObject, "AddressShipping");
            Value &AddressBillingValue = JsonUtils::getJsonObject(aJsonObject, "AddressBilling");

            parseValueAddress(AddressBillingValue, &m_AddressBilling);
            parseValueAddress(AddressShippingValue, &m_AddressShipping);

            Value &StatusesValue = JsonUtils::getJsonArray(aJsonObject, "Statuses");
            if (!StatusesValue.IsNull())
            {
                m_Statuses.m_Status = JsonUtils::tryGetString(StatusesValue, "0", "");
            }
        }
        catch (JsonException ex)
        {
            qDebug() << "LazadaDataItemOrderItem::parseItemData ERORR: " << ex.what();
        }
    }
}

void LazadaDataItemOrder::parseValueAddress(Value &aObject, Address *address)
{
    if (!aObject.IsNull())
    {
        try
        {
            address->m_FirstName = JsonUtils::tryGetString(aObject, "FirstName", "");
            address->m_LastName = JsonUtils::tryGetString(aObject, "LastName", "");
            address->m_Phone = JsonUtils::tryGetString(aObject, "Phone", "");
            address->m_Phone2 = JsonUtils::tryGetString(aObject, "Phone2", "");
            address->m_Address1 = JsonUtils::tryGetString(aObject, "Address1", "");
            address->m_Address2 = JsonUtils::tryGetString(aObject, "Address2", "");
            address->m_Address3 = JsonUtils::tryGetString(aObject, "Address3", "");
            address->m_Address4 = JsonUtils::tryGetString(aObject, "Address4", "");
            address->m_Address5 = JsonUtils::tryGetString(aObject, "Address5", "");
            address->m_CustomerEmail = JsonUtils::tryGetString(aObject, "CustomerEmail", "");
            address->m_City = JsonUtils::tryGetString(aObject, "City", "");
            address->m_PostCode = JsonUtils::tryGetString(aObject, "PostCode", "");
            address->m_Country = JsonUtils::tryGetString(aObject, "Country", "");
        }
        catch (JsonException ex)
        {
            qDebug() << "LazadaDataItemOrderItem::parseValueAddress ERORR: " << ex.what();
        }
    }
}
