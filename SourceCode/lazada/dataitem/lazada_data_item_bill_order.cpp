#include "lazada_data_item_bill_order.h"
#include "../../core/jsonutil/json_utils.h"
#include "../../core/jsonutil/json_exception.h"
#include <QDebug>

using namespace Core::Json;
using namespace Core::DataItem;

LazadaDataItemBillOrder::LazadaDataItemBillOrder()
{

}

Core::DataItem::AbstractDataItem *Core::DataItem::LazadaDataItemBillOrder::clone() const
{
    return new LazadaDataItemBillOrder(*this);
}

void Core::DataItem::LazadaDataItemBillOrder::parseItemData(Value &aJsonObject)
{
    if (!aJsonObject.IsNull())
    {
        try
        {
            m_OrderItemId = JsonUtils::tryGetLong(aJsonObject, "OrderItemId", -1);
            m_ShopId = JsonUtils::tryGetString(aJsonObject, "ShopId", "");
            m_OrderId = JsonUtils::tryGetLong(aJsonObject, "OrderId", -1);
            m_Name = JsonUtils::tryGetString(aJsonObject, "Name", "");
            m_Sku = JsonUtils::tryGetString(aJsonObject, "Sku", "");
            m_ShopSku = JsonUtils::tryGetString(aJsonObject, "ShopSku", "");
            m_ShippingType = JsonUtils::tryGetString(aJsonObject, "ShippingType", "");
            m_ItemPrice = JsonUtils::tryGetLong(aJsonObject, "ItemPrice", 0);
            m_PaidPrice = JsonUtils::tryGetLong(aJsonObject, "PaidPrice", 0);
            m_Currency = JsonUtils::tryGetString(aJsonObject, "Currency", "");
            m_WalletCredits = JsonUtils::tryGetInt(aJsonObject, "WalletCredits", 0);
            m_TaxAmount = JsonUtils::tryGetInt(aJsonObject, "TaxAmount", 0);
            m_ShippingAmount = JsonUtils::tryGetInt(aJsonObject, "ShippingAmount", 0);
            m_ShippingServiceCode = JsonUtils::tryGetInt(aJsonObject, "ShippingServiceCost", 0);
            m_VoucherAmount = JsonUtils::tryGetLong(aJsonObject, "VoucherAmount", 0);
            m_VoucherCode = JsonUtils::tryGetString(aJsonObject, "VoucherCode", "");
            m_Status = JsonUtils::tryGetString(aJsonObject, "Status", "");
            m_ShipmentProvider = JsonUtils::tryGetString(aJsonObject, "ShipmentProvider", "");
            m_IsDigital = JsonUtils::tryGetInt(aJsonObject, "IsDigital", 0);
            m_DigitalDeliveryInfo = JsonUtils::tryGetString(aJsonObject, "DigitalDeliveryInfo", "");
            m_TrackingCode = JsonUtils::tryGetString(aJsonObject, "TrackingCode", "");
            m_TrackingCodePre = JsonUtils::tryGetString(aJsonObject, "TrackingCodePre", "");
            m_Reason = JsonUtils::tryGetString(aJsonObject, "Reason", "");
            m_ReasonDetail = JsonUtils::tryGetString(aJsonObject, "ReasonDetail", "");
            m_PurchaseOrderId = JsonUtils::tryGetString(aJsonObject, "PurchaseOrderId", "");
            m_PurchaseOrderNumber = JsonUtils::tryGetString(aJsonObject, "PurchaseOrderNumber", "");
            m_PackageId = JsonUtils::tryGetString(aJsonObject, "PackageId", "");
            m_PromisedShippingTime = JsonUtils::tryGetString(aJsonObject, "PromisedShippingTime", "");
            m_ExtraAttributes = JsonUtils::tryGetString(aJsonObject, "ExtraAttributes", "");
            m_ShippingProviderType = JsonUtils::tryGetString(aJsonObject, "ShippingProviderType", "");
            m_CreatedAt = JsonUtils::tryGetString(aJsonObject, "CreatedAt", "");
            m_UpdatedAt = JsonUtils::tryGetString(aJsonObject, "UpdatedAt", "");
            m_ReturnStatus = JsonUtils::tryGetString(aJsonObject, "ReturnStatus", "");
            m_productMainImage = JsonUtils::tryGetString(aJsonObject, "productMainImage", "");
            m_Variation = JsonUtils::tryGetString(aJsonObject, "Variation", "");
            m_ProductDetailUrl = JsonUtils::tryGetString(aJsonObject, "ProductDetailUrl", "");
            m_invoiceNumber = JsonUtils::tryGetString(aJsonObject, "invoiceNumber", "");

        }
        catch (JsonException ex)
        {
            qDebug() << "LazadaDataItemOrderItem::parseItemData ERORR: " << ex.what();
        }
    }
}

QString LazadaDataItemBillOrder::ShopId() const
{
    return m_ShopId;
}

QString LazadaDataItemBillOrder::Sku() const
{
    return m_Sku;
}

QString LazadaDataItemBillOrder::ShopSku() const
{
    return m_ShopSku;
}

QString LazadaDataItemBillOrder::ShippingType() const
{
    return m_ShippingType;
}

QString LazadaDataItemBillOrder::Currency() const
{
    return m_Currency;
}

QString LazadaDataItemBillOrder::Name() const
{
    return m_Name;
}

QString LazadaDataItemBillOrder::VoucherCode() const
{
    return m_VoucherCode;
}

QString LazadaDataItemBillOrder::Status() const
{
    return m_Status;
}

QString LazadaDataItemBillOrder::ShipmentProvider() const
{
    return m_ShipmentProvider;
}

QString LazadaDataItemBillOrder::DigitalDeliveryInfo() const
{
    return m_DigitalDeliveryInfo;
}

QString LazadaDataItemBillOrder::TrackingCode() const
{
    return m_TrackingCode;
}

QString LazadaDataItemBillOrder::TrackingCodePre() const
{
    return m_TrackingCodePre;
}

QString LazadaDataItemBillOrder::Reason() const
{
    return m_Reason;
}

QString LazadaDataItemBillOrder::ReasonDetail() const
{
    return m_ReasonDetail;
}

QString LazadaDataItemBillOrder::PurchaseOrderId() const
{
    return m_PurchaseOrderId;
}

QString LazadaDataItemBillOrder::PurchaseOrderNumber() const
{
    return m_PurchaseOrderNumber;
}

QString LazadaDataItemBillOrder::PackageId() const
{
    return m_PackageId;
}

QString LazadaDataItemBillOrder::PromisedShippingTime() const
{
    return m_PromisedShippingTime;
}

QString LazadaDataItemBillOrder::ExtraAttributes() const
{
    return m_ExtraAttributes;
}

QString LazadaDataItemBillOrder::ShippingProviderType() const
{
    return m_ShippingProviderType;
}

QString LazadaDataItemBillOrder::CreatedAt() const
{
    return m_CreatedAt;
}

QString LazadaDataItemBillOrder::UpdatedAt() const
{
    return m_UpdatedAt;
}

QString LazadaDataItemBillOrder::ReturnStatus() const
{
    return m_ReturnStatus;
}

QString LazadaDataItemBillOrder::productMainImage() const
{
    return m_productMainImage;
}

QString LazadaDataItemBillOrder::Variation() const
{
    return m_Variation;
}

QString LazadaDataItemBillOrder::ProductDetailUrl() const
{
    return m_ProductDetailUrl;
}

QString LazadaDataItemBillOrder::invoiceNumber() const
{
    return m_invoiceNumber;
}

qint64 LazadaDataItemBillOrder::OrderId() const
{
    return m_OrderId;
}

qint64 LazadaDataItemBillOrder::OrderItemId() const
{
    return m_OrderItemId;
}

qint64 LazadaDataItemBillOrder::ItemPrice() const
{
    return m_ItemPrice;
}

qint64 LazadaDataItemBillOrder::PaidPrice() const
{
    return m_PaidPrice;
}

qint64 LazadaDataItemBillOrder::VoucherAmount() const
{
    return m_VoucherAmount;
}

int LazadaDataItemBillOrder::WalletCredits() const
{
    return m_WalletCredits;
}

int LazadaDataItemBillOrder::TaxAmount() const
{
    return m_TaxAmount;
}

int LazadaDataItemBillOrder::ShippingAmount() const
{
    return m_ShippingAmount;
}

int LazadaDataItemBillOrder::ShippingServiceCode() const
{
    return m_ShippingServiceCode;
}

int LazadaDataItemBillOrder::IsDigital() const
{
    return m_IsDigital;
}
