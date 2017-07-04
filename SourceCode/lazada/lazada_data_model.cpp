#include "lazada_data_model.h"
#include <QHash>

using namespace Lazada::DataModel;

DataOrder::DataOrder() {}

void DataOrder::updateData(DataOrder *newOrder)
{
    setAddressBilling(newOrder->getAddressBilling());
    setAddressShipping(newOrder->getAddressShipping());
    setCreatedAt(newOrder->getCreatedAt());
    setCustomerFullName(newOrder->getCustomerFullName());
    setGiftMessage(newOrder->getGiftMessage());
    setGiftOption(newOrder->getGiftOption());
    setItemCount(newOrder->getItemCount());
    setListStatuses(newOrder->getListStatuses());
    setOrderId(newOrder->getOrderId());
    setOrderNumber(newOrder->getOrderNumber());
    setPaymentMethod(newOrder->getPaymentMethod());
    setPrice(newOrder->getPrice());
    setUpdatedAt(newOrder->getUpdatedAt());
    setVoucherCode(newOrder->getVoucherCode());
}

void DataOrder::setOrderId(const uint32_t orderId)
{
    m_OrderId = orderId;
}

uint32_t DataOrder::getOrderId() const
{
    return m_OrderId;
}

void DataOrder::setItemCount(const int32_t itemCount)
{
    m_ItemCount = itemCount;
}

int32_t DataOrder::getItemCount() const
{
    return m_ItemCount;
}

void DataOrder::setCustomerFullName(const QString &fullName)
{
    m_strCustomerFullName = fullName;
}

QString DataOrder::getCustomerFullName() const
{
    return m_strCustomerFullName;
}

void DataOrder::setUpdatedAt(const QString &updatedAt)
{
    m_strUpdatedAt = updatedAt;
}

QString DataOrder::getUpdatedAt() const
{
    return m_strUpdatedAt;
}

void DataOrder::setCreatedAt(const QString &createdAt)
{
    m_strCreatedAt = createdAt;
}

QString DataOrder::getCreatedAt() const
{
    return m_strCreatedAt;
}

void DataOrder::setAddressBilling(const QString &addressBilling)
{
    m_strAddressBilling = addressBilling;
}

QString DataOrder::getAddressBilling() const
{
    return m_strAddressBilling;
}

void DataOrder::setAddressShipping(const QString &addressShipping)
{
    m_strAddressShipping = addressShipping;
}

QString DataOrder::getAddressShipping() const
{
    return m_strAddressShipping;
}

void DataOrder::setPaymentMethod(const QString &paymentMethod)
{
    m_strPaymentMethod = paymentMethod;
}

QString DataOrder::getPaymentMethod() const
{
    return m_strPaymentMethod;
}

void DataOrder::setListStatuses(const QStringList &listStatuses)
{
    m_listStatuses = listStatuses;
}

QStringList DataOrder::getListStatuses() const
{
    return m_listStatuses;
}

bool DataOrder::getGiftOption() const
{
    return m_GiftOption;
}

QHash<uint32_t, DataOrderItem *> *DataOrder::getHashOrderItems() const
{
    return m_hashOrderItems;
}

QList<DataOrderItem *> *DataOrder::getListOrderItems() const
{
    return m_listOrderItems;
}

void DataOrder::updateOrderItems(DataOrderItem *orderItem)
{
    if (!orderItem) return;

    if (!m_hashOrderItems)
    {
        m_hashOrderItems = new QHash<uint32_t, DataOrderItem *>();
    }

    m_hashOrderItems->insert(orderItem->getOrderItemId(), orderItem);

    if (!m_listOrderItems)
    {
        m_listOrderItems = new QList<DataOrderItem *>();
    }
    m_listOrderItems->append(orderItem);
}

uint32_t DataOrder::getOrderNumber() const
{
    return m_OrderNumber;
}

void DataOrder::setOrderNumber(const uint32_t &OrderNumber)
{
    m_OrderNumber = OrderNumber;
}

QString DataOrder::getPrice() const
{
    return m_strPrice;
}

void DataOrder::setPrice(const QString &price)
{
    m_strPrice = price;
}

QString DataOrder::getVoucherCode() const
{
    return m_strVoucherCode;
}

void DataOrder::setVoucherCode(const QString &voucherCode)
{
    m_strVoucherCode = voucherCode;
}

QString DataOrder::getGiftMessage() const
{
    return m_strGiftMessage;
}

void DataOrder::setGiftMessage(const QString &giftMessage)
{
    m_strGiftMessage = giftMessage;
}

void DataOrder::setGiftOption(bool GiftOption)
{
    m_GiftOption = GiftOption;
}

//------------DataOrderItem-----------//


uint32_t DataOrderItem::getOrderItemId() const
{
    return m_orderItemId;
}

void DataOrderItem::setOrderItemId(const uint32_t &orderItemId)
{
    m_orderItemId = orderItemId;
}

void DataOrderItem::updateData(DataOrderItem *newOrderItem)
{
    setCreatedAt(newOrderItem->getCreatedAt());
    setInvoiceNumber(newOrderItem->getInvoiceNumber());
    setNameOrderItem(newOrderItem->getNameOrderItem());
    setOrderId(newOrderItem->getOrderId());
    setOrderItemId(newOrderItem->getOrderItemId());
    setPackageId(newOrderItem->getPackageId());
    setProductDetailUrl(newOrderItem->getProductDetailUrl());
    setProductMainImage(newOrderItem->getProductMainImage());
    setPurchaseOrderId(newOrderItem->getPurchaseOrderId());
    setPurchaseOrderNumber(newOrderItem->getPurchaseOrderNumber());
    setShipmentProvider(newOrderItem->getShipmentProvider());
    setShippingType(newOrderItem->getShippingType());
    setShopId(newOrderItem->getShopId());
    setShopSku(newOrderItem->getShopSku());
    setSku(newOrderItem->getSku());
    setStatus(newOrderItem->getStatus());
    setTrackingCode(newOrderItem->getTrackingCode());
    setUpdatedAt(newOrderItem->getUpdatedAt());
}

uint32_t DataOrderItem::getOrderId() const
{
    return m_orderId;
}

void DataOrderItem::setOrderId(const uint32_t &orderId)
{
    m_orderId = orderId;
}

QString DataOrderItem::getShopId() const
{
    return m_ShopId;
}

void DataOrderItem::setShopId(const QString &ShopId)
{
    m_ShopId = ShopId;
}

QString DataOrderItem::getNameOrderItem() const
{
    return m_NameOrderItem;
}

void DataOrderItem::setNameOrderItem(const QString &NameOrderItem)
{
    m_NameOrderItem = NameOrderItem;
}

QString DataOrderItem::getSku() const
{
    return m_Sku;
}

void DataOrderItem::setSku(const QString &Sku)
{
    m_Sku = Sku;
}

QString DataOrderItem::getShopSku() const
{
    return m_ShopSku;
}

void DataOrderItem::setShopSku(const QString &ShopSku)
{
    m_ShopSku = ShopSku;
}

QString DataOrderItem::getShippingType() const
{
    return m_ShippingType;
}

void DataOrderItem::setShippingType(const QString &ShippingType)
{
    m_ShippingType = ShippingType;
}

QString DataOrderItem::getStatus() const
{
    return m_Status;
}

void DataOrderItem::setStatus(const QString &Status)
{
    m_Status = Status;
}

QString DataOrderItem::getShipmentProvider() const
{
    return m_ShipmentProvider;
}

void DataOrderItem::setShipmentProvider(const QString &ShipmentProvider)
{
    m_ShipmentProvider = ShipmentProvider;
}

QString DataOrderItem::getPurchaseOrderNumber() const
{
    return m_PurchaseOrderNumber;
}

void DataOrderItem::setPurchaseOrderNumber(const QString &PurchaseOrderNumber)
{
    m_PurchaseOrderNumber = PurchaseOrderNumber;
}

QString DataOrderItem::getPackageId() const
{
    return m_PackageId;
}

void DataOrderItem::setPackageId(const QString &PackageId)
{
    m_PackageId = PackageId;
}

QString DataOrderItem::getProductMainImage() const
{
    return m_productMainImage;
}

void DataOrderItem::setProductMainImage(const QString &productMainImage)
{
    m_productMainImage = productMainImage;
}

QString DataOrderItem::getProductDetailUrl() const
{
    return m_ProductDetailUrl;
}

void DataOrderItem::setProductDetailUrl(const QString &ProductDetailUrl)
{
    m_ProductDetailUrl = ProductDetailUrl;
}

QString DataOrderItem::getInvoiceNumber() const
{
    return m_invoiceNumber;
}

void DataOrderItem::setInvoiceNumber(const QString &invoiceNumber)
{
    m_invoiceNumber = invoiceNumber;
}

QString DataOrderItem::getCreatedAt() const
{
    return m_CreatedAt;
}

void DataOrderItem::setCreatedAt(const QString &CreatedAt)
{
    m_CreatedAt = CreatedAt;
}

QString DataOrderItem::getUpdatedAt() const
{
    return m_UpdatedAt;
}

void DataOrderItem::setUpdatedAt(const QString &UpdatedAt)
{
    m_UpdatedAt = UpdatedAt;
}

QString DataOrderItem::getPurchaseOrderId() const
{
    return m_PurchaseOrderId;
}

void DataOrderItem::setPurchaseOrderId(const QString &PurchaseOrderId)
{
    m_PurchaseOrderId = PurchaseOrderId;
}

QString DataOrderItem::getTrackingCode() const
{
    return m_TrackingCode;
}

void DataOrderItem::setTrackingCode(const QString &TrackingCode)
{
    m_TrackingCode = TrackingCode;
}
