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
