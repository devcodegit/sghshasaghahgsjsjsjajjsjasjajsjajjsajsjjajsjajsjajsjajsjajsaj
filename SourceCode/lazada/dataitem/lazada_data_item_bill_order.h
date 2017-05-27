#ifndef LAZADA_DATA_ITEM_BILL_ORDER_H
#define LAZADA_DATA_ITEM_BILL_ORDER_H

#include "../../core/dataitem/abstract_data_item.h"

namespace Core { namespace DataItem {

    class LazadaDataItemBillOrder : public AbstractDataItem
    {
    public:
        LazadaDataItemBillOrder();

        virtual AbstractDataItem* clone() const;
        virtual void parseItemData(Value& aJsonObject);

        QString ShopId() const;
        QString Sku() const;
        QString ShopSku() const;
        QString ShippingType() const;
        QString Currency() const;
        QString Name() const;
        QString VoucherCode() const;
        QString Status() const;
        QString ShipmentProvider() const;
        QString DigitalDeliveryInfo() const;
        QString TrackingCode() const;
        QString TrackingCodePre() const;
        QString Reason() const;
        QString ReasonDetail() const;
        QString PurchaseOrderId() const;
        QString PurchaseOrderNumber() const;
        QString PackageId() const;
        QString PromisedShippingTime() const;
        QString ExtraAttributes() const;
        QString ShippingProviderType() const;
        QString CreatedAt() const;
        QString UpdatedAt() const;
        QString ReturnStatus() const;
        QString productMainImage() const;
        QString Variation() const;
        QString ProductDetailUrl() const;
        QString invoiceNumber() const;

        qint64 OrderId() const;
        qint64 OrderItemId() const;
        qint64 ItemPrice() const;
        qint64 PaidPrice() const;
        qint64 VoucherAmount() const;

        int WalletCredits() const;
        int TaxAmount() const;
        int ShippingAmount() const;
        int ShippingServiceCode() const;
        int IsDigital() const;

    private:
        QString m_ShopId;
        QString m_Sku;
        QString m_ShopSku;
        QString m_ShippingType;
        QString m_Currency;
        QString m_Name;
        QString m_VoucherCode;
        QString m_Status;
        QString m_ShipmentProvider;
        QString m_DigitalDeliveryInfo;
        QString m_TrackingCode;
        QString m_TrackingCodePre;
        QString m_Reason;
        QString m_ReasonDetail;
        QString m_PurchaseOrderId;
        QString m_PurchaseOrderNumber;
        QString m_PackageId;
        QString m_PromisedShippingTime;
        QString m_ExtraAttributes;
        QString m_ShippingProviderType;
        QString m_CreatedAt;
        QString m_UpdatedAt;
        QString m_ReturnStatus;
        QString m_productMainImage;
        QString m_Variation;
        QString m_ProductDetailUrl;
        QString m_invoiceNumber;

        qint64 m_OrderId = -1;
        qint64 m_OrderItemId = -1;
        qint64 m_ItemPrice = 0;
        qint64 m_PaidPrice = 0;
        qint64 m_VoucherAmount = 0;

        int m_WalletCredits = 0;
        int m_TaxAmount = 0;
        int m_ShippingAmount = 0;
        int m_ShippingServiceCode = 0;
        int m_IsDigital = 0;

    };

}}

#endif // LAZADA_DATA_ITEM_BILL_ORDER_H
