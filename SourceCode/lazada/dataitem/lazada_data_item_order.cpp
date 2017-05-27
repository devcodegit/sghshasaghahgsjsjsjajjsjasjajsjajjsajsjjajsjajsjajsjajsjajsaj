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

void LazadaDataItemOrder::cloneData(LazadaDataItemOrder *dataClone)
{
    if (!dataClone) return;
    dataClone->m_AddressBilling = this->m_AddressBilling;
    dataClone->m_AddressShipping = this->m_AddressShipping;
    dataClone->m_Statuses = this->m_Statuses;
    dataClone->m_CustomerFirstName = this->m_CustomerFirstName;
    dataClone->m_CustomerLastName = this->m_CustomerLastName;
    dataClone->m_PaymentMethod = this->m_PaymentMethod;
    dataClone->m_Remarks = this->m_Remarks;
    dataClone->m_DeliveryInfo = this->m_DeliveryInfo;
    dataClone->m_Price = this->m_Price;
    dataClone->m_GiftMessage = this->m_GiftMessage;
    dataClone->m_VoucherCode = this->m_VoucherCode;
    dataClone->m_CreatedAt = this->m_CreatedAt;
    dataClone->m_UpdatedAt = this->m_UpdatedAt;
    dataClone->m_NationalRegistrationNumber = this->m_NationalRegistrationNumber;
    dataClone->m_PromisedShippingTimes = this->m_PromisedShippingTimes;
    dataClone->m_ExtraAttributes = this->m_ExtraAttributes;
    dataClone->m_OrderNumber = this->m_OrderNumber;
    dataClone->m_OrderId = this->m_OrderId;
    dataClone->m_GiftOption = this->m_GiftOption;
    dataClone->m_ItemsCount = this->m_ItemsCount;
    dataClone->m_Voucher = this->m_Voucher;
    dataClone->m_ShippingFee = this->m_ShippingFee;
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

int LazadaDataItemOrder::getShippingFee() const
{
    return m_ShippingFee;
}

void LazadaDataItemOrder::setShippingFee(int ShippingFee)
{
    m_ShippingFee = ShippingFee;
}

int LazadaDataItemOrder::getVoucher() const
{
    return m_Voucher;
}

void LazadaDataItemOrder::setVoucher(int Voucher)
{
    m_Voucher = Voucher;
}

int LazadaDataItemOrder::getItemsCount() const
{
    return m_ItemsCount;
}

void LazadaDataItemOrder::setItemsCount(int ItemsCount)
{
    m_ItemsCount = ItemsCount;
}

bool LazadaDataItemOrder::getGiftOption() const
{
    return m_GiftOption;
}

void LazadaDataItemOrder::setGiftOption(bool GiftOption)
{
    m_GiftOption = GiftOption;
}

qint64 LazadaDataItemOrder::getOrderNumber() const
{
    return m_OrderNumber;
}

void LazadaDataItemOrder::setOrderNumber(const qint64 &OrderNumber)
{
    m_OrderNumber = OrderNumber;
}

QString LazadaDataItemOrder::getExtraAttributes() const
{
    return m_ExtraAttributes;
}

void LazadaDataItemOrder::setExtraAttributes(const QString &ExtraAttributes)
{
    m_ExtraAttributes = ExtraAttributes;
}

QString LazadaDataItemOrder::getPromisedShippingTimes() const
{
    return m_PromisedShippingTimes;
}

void LazadaDataItemOrder::setPromisedShippingTimes(const QString &PromisedShippingTimes)
{
    m_PromisedShippingTimes = PromisedShippingTimes;
}

QString LazadaDataItemOrder::getNationalRegistrationNumber() const
{
    return m_NationalRegistrationNumber;
}

void LazadaDataItemOrder::setNationalRegistrationNumber(const QString &NationalRegistrationNumber)
{
    m_NationalRegistrationNumber = NationalRegistrationNumber;
}

QString LazadaDataItemOrder::getUpdatedAt() const
{
    return m_UpdatedAt;
}

void LazadaDataItemOrder::setUpdatedAt(const QString &UpdatedAt)
{
    m_UpdatedAt = UpdatedAt;
}

QString LazadaDataItemOrder::getCreatedAt() const
{
    return m_CreatedAt;
}

void LazadaDataItemOrder::setCreatedAt(const QString &CreatedAt)
{
    m_CreatedAt = CreatedAt;
}

QString LazadaDataItemOrder::getVoucherCode() const
{
    return m_VoucherCode;
}

void LazadaDataItemOrder::setVoucherCode(const QString &VoucherCode)
{
    m_VoucherCode = VoucherCode;
}

QString LazadaDataItemOrder::getGiftMessage() const
{
    return m_GiftMessage;
}

void LazadaDataItemOrder::setGiftMessage(const QString &GiftMessage)
{
    m_GiftMessage = GiftMessage;
}

QString LazadaDataItemOrder::getPrice() const
{
    return m_Price;
}

void LazadaDataItemOrder::setPrice(const QString &Price)
{
    m_Price = Price;
}

QString LazadaDataItemOrder::getDeliveryInfo() const
{
    return m_DeliveryInfo;
}

void LazadaDataItemOrder::setDeliveryInfo(const QString &DeliveryInfo)
{
    m_DeliveryInfo = DeliveryInfo;
}

QString LazadaDataItemOrder::getRemarks() const
{
    return m_Remarks;
}

void LazadaDataItemOrder::setRemarks(const QString &Remarks)
{
    m_Remarks = Remarks;
}

QString LazadaDataItemOrder::getPaymentMethod() const
{
    return m_PaymentMethod;
}

void LazadaDataItemOrder::setPaymentMethod(const QString &PaymentMethod)
{
    m_PaymentMethod = PaymentMethod;
}

QString LazadaDataItemOrder::getCustomerLastName() const
{
    return m_CustomerLastName;
}

void LazadaDataItemOrder::setCustomerLastName(const QString &CustomerLastName)
{
    m_CustomerLastName = CustomerLastName;
}

QString LazadaDataItemOrder::getCustomerFirstName() const
{
    return m_CustomerFirstName;
}

void LazadaDataItemOrder::setCustomerFirstName(const QString &CustomerFirstName)
{
    m_CustomerFirstName = CustomerFirstName;
}

void LazadaDataItemOrder::setStatuses(const Statuses &Statuses)
{
    m_Statuses = Statuses;
}

LazadaDataItemOrder::Address LazadaDataItemOrder::AddressShipping() const
{
    return m_AddressShipping;
}

void LazadaDataItemOrder::setAddressShipping(const Address &AddressShipping)
{
    m_AddressShipping = AddressShipping;
}

LazadaDataItemOrder::Statuses LazadaDataItemOrder::getStatuses() const
{
    return m_Statuses;
}

LazadaDataItemOrder::Address LazadaDataItemOrder::AddressBilling() const
{
    return m_AddressBilling;
}

void LazadaDataItemOrder::setAddressBilling(const Address &AddressBilling)
{
    m_AddressBilling = AddressBilling;
}

void LazadaDataItemOrder::setOrderId(const qint64 &OrderId)
{
    m_OrderId = OrderId;
}

qint64 LazadaDataItemOrder::OrderId() const
{
    return m_OrderId;
}
