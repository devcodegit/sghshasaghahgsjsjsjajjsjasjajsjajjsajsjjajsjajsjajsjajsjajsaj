#ifndef LAZADA_DATA_MODEL_H
#define LAZADA_DATA_MODEL_H

#include "../global.h"
#include <QString>
#include <QHash>
#include <QStringList>

namespace Lazada { namespace DataModel {

    class DataOrderItem
    {
    public:
        DataOrderItem() {}

        void updateData(DataOrderItem *newOrderItem);

        uint32_t getOrderItemId() const;
        void setOrderItemId(const uint32_t &orderItemId);

        uint32_t getOrderId() const;
        void setOrderId(const uint32_t &orderId);

        QString getShopId() const;
        void setShopId(const QString &ShopId);

        QString getNameOrderItem() const;
        void setNameOrderItem(const QString &NameOrderItem);

        QString getSku() const;
        void setSku(const QString &Sku);

        QString getShopSku() const;
        void setShopSku(const QString &ShopSku);

        QString getShippingType() const;
        void setShippingType(const QString &ShippingType);

        QString getStatus() const;
        void setStatus(const QString &Status);

        QString getShipmentProvider() const;
        void setShipmentProvider(const QString &ShipmentProvider);

        QString getPurchaseOrderNumber() const;
        void setPurchaseOrderNumber(const QString &PurchaseOrderNumber);

        QString getPackageId() const;
        void setPackageId(const QString &PackageId);

        QString getProductMainImage() const;
        void setProductMainImage(const QString &productMainImage);

        QString getProductDetailUrl() const;
        void setProductDetailUrl(const QString &ProductDetailUrl);

        QString getInvoiceNumber() const;
        void setInvoiceNumber(const QString &invoiceNumber);

        QString getCreatedAt() const;
        void setCreatedAt(const QString &CreatedAt);

        QString getUpdatedAt() const;
        void setUpdatedAt(const QString &UpdatedAt);

        QString getPurchaseOrderId() const;
        void setPurchaseOrderId(const QString &PurchaseOrderId);

        QString getTrackingCode() const;
        void setTrackingCode(const QString &TrackingCode);

    private:
        uint32_t m_orderItemId = 0;
        uint32_t m_orderId = 0;

        QString m_ShopId;
        QString m_NameOrderItem;
        QString m_Sku;
        QString m_ShopSku;
        QString m_ShippingType;

        QString m_Status;
        QString m_ShipmentProvider;
        QString m_TrackingCode;
        QString m_PurchaseOrderId;
        QString m_PurchaseOrderNumber;
        QString m_PackageId;
        QString m_invoiceNumber;

        QString m_productMainImage;
        QString m_ProductDetailUrl;

        QString m_CreatedAt;
        QString m_UpdatedAt;
    };

    class DataOrder
    {
    public:
        DataOrder();

        void updateData(DataOrder *newOrder);

    public:
        void setOrderId(const uint32_t orderId);
        uint32_t getOrderId() const;

        void setOrderNumber(const uint32_t &OrderNumber);
        uint32_t getOrderNumber() const;

        void setItemCount(const int32_t itemCount);
        int32_t getItemCount() const;

        void setCustomerFullName(const QString &fullName);
        QString getCustomerFullName() const;

        void setUpdatedAt(const QString &updatedAt);
        QString getUpdatedAt() const;

        void setCreatedAt(const QString &createdAt);
        QString getCreatedAt() const;

        void setAddressBilling(const QString &addressBilling);
        QString getAddressBilling() const;

        void setAddressShipping(const QString &addressShipping);
        QString getAddressShipping() const;

        void setPaymentMethod(const QString &paymentMethod);
        QString getPaymentMethod() const;

        void setGiftMessage(const QString &giftMessage);
        QString getGiftMessage() const;

        void setVoucherCode(const QString &voucherCode);
        QString getVoucherCode() const;

        void setPrice(const QString &price);
        QString getPrice() const;

        void setListStatuses(const QStringList &listStatuses);
        QStringList getListStatuses() const;

        void setGiftOption(bool GiftOption);
        bool getGiftOption() const;

        QHash<uint32_t, DataOrderItem *> *getHashOrderItems() const;
        QList<DataOrderItem *> *getListOrderItems() const;

        void updateOrderItems(DataOrderItem *orderItem);

    private:
        uint32_t m_OrderId = 0;
        uint32_t m_OrderNumber = 0;
        int32_t m_ItemCount = 0;

        QString m_strCustomerFullName;
        QString m_strCreatedAt;
        QString m_strUpdatedAt;
        QString m_strAddressBilling;
        QString m_strAddressShipping;
        QString m_strPaymentMethod;
        QString m_strGiftMessage;
        QString m_strVoucherCode;
        QString m_strPrice;

        QStringList m_listStatuses;

        QHash<uint32_t, DataOrderItem *> *m_hashOrderItems = NULL;
        QList<DataOrderItem *> *m_listOrderItems = NULL;

        bool m_GiftOption;
    };

}}

#endif // LAZADA_DATA_MODEL_H
