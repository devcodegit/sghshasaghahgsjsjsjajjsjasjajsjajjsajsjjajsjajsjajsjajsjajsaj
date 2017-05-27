#ifndef LAZADA_DATA_ITEM_ORDER_H
#define LAZADA_DATA_ITEM_ORDER_H

#include "../../core/dataitem/abstract_data_item.h"

namespace Core { namespace DataItem {

    class LazadaDataItemOrder : public AbstractDataItem
    {
    public:
        LazadaDataItemOrder();

        virtual AbstractDataItem* clone() const;
        virtual void parseItemData(Value& aJsonObject);
        void cloneData(LazadaDataItemOrder *dataClone);

        struct Address
        {
            QString m_FirstName;
            QString m_LastName;
            QString m_Phone;
            QString m_Phone2;
            QString m_Address1;
            QString m_Address2;
            QString m_Address3;
            QString m_Address4;
            QString m_Address5;
            QString m_CustomerEmail;
            QString m_City;
            QString m_PostCode;
            QString m_Country;
        };

        struct Statuses
        {
            QString m_Status;
        };

        qint64 OrderId() const;
        void setOrderId(const qint64 &OrderId);

        Address AddressBilling() const;
        void setAddressBilling(const Address &AddressBilling);

        Address AddressShipping() const;
        void setAddressShipping(const Address &AddressShipping);

        Statuses getStatuses() const;
        void setStatuses(const Statuses &Statuses);

        QString getCustomerFirstName() const;
        void setCustomerFirstName(const QString &CustomerFirstName);

        QString getCustomerLastName() const;
        void setCustomerLastName(const QString &CustomerLastName);

        QString getPaymentMethod() const;
        void setPaymentMethod(const QString &PaymentMethod);

        QString getRemarks() const;
        void setRemarks(const QString &Remarks);

        QString getDeliveryInfo() const;
        void setDeliveryInfo(const QString &DeliveryInfo);

        QString getPrice() const;
        void setPrice(const QString &Price);

        QString getGiftMessage() const;
        void setGiftMessage(const QString &GiftMessage);

        QString getVoucherCode() const;
        void setVoucherCode(const QString &VoucherCode);

        QString getCreatedAt() const;
        void setCreatedAt(const QString &CreatedAt);

        QString getUpdatedAt() const;
        void setUpdatedAt(const QString &UpdatedAt);

        QString getNationalRegistrationNumber() const;
        void setNationalRegistrationNumber(const QString &NationalRegistrationNumber);

        QString getPromisedShippingTimes() const;
        void setPromisedShippingTimes(const QString &PromisedShippingTimes);

        QString getExtraAttributes() const;
        void setExtraAttributes(const QString &ExtraAttributes);

        qint64 getOrderNumber() const;
        void setOrderNumber(const qint64 &OrderNumber);

        bool getGiftOption() const;
        void setGiftOption(bool GiftOption);

        int getItemsCount() const;
        void setItemsCount(int ItemsCount);

        int getVoucher() const;
        void setVoucher(int Voucher);

        int getShippingFee() const;
        void setShippingFee(int ShippingFee);

    private:
        void parseValueAddress(Value &aObject, Address *address);

    private:
        Address m_AddressBilling;
        Address m_AddressShipping;
        Statuses m_Statuses;

        QString m_CustomerFirstName;
        QString m_CustomerLastName;
        QString m_PaymentMethod;
        QString m_Remarks;
        QString m_DeliveryInfo;
        QString m_Price;
        QString m_GiftMessage;
        QString m_VoucherCode;
        QString m_CreatedAt;
        QString m_UpdatedAt;
        QString m_NationalRegistrationNumber;
        QString m_PromisedShippingTimes;
        QString m_ExtraAttributes;

        qint64 m_OrderNumber = -1;
        qint64 m_OrderId = -1;

        bool m_GiftOption;

        int m_ItemsCount = 0;
        int m_Voucher = 0;
        int m_ShippingFee = 0;

    };

}}

#endif // LAZADA_DATA_ITEM_ORDER_H
