#include "detailwidget.h"
#include "../../lazada/lazada_data_model.h"
#include "verticalscrollbar.h"
#include <QFrame>
#include <QBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QScrollArea>
#include <QScrollBar>

#define DIALOG_HEIGHT 300
#define DIALOG_WIDTH 500

using namespace Lazada::DataModel;

DetailWidget::DetailWidget(QWidget *parent) : SDialog(parent)
{
    setWindowTitle("Thông tin đơn hàng");
    QFrame *bg = new QFrame;
    bg->setFixedSize(DIALOG_WIDTH, DIALOG_HEIGHT);

    scroll = new QWidget;
    scroll->setFixedWidth(DIALOG_WIDTH);
    scroll->setObjectName("TransWg");
    scroll->move(0,0);
    scrollArea = new QScrollArea(bg);
    scrollArea->setFixedSize(DIALOG_WIDTH - 2, DIALOG_HEIGHT);
    scrollArea->setFocusPolicy(Qt::NoFocus);
    scrollArea->setWidget(scroll);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    scrollArea->move(0,0);
    scrollArea->show();
    connect(scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollValueChanged(int)));
    scrollBar = new VerticalScrollbar(scrollArea, scrollArea->verticalScrollBar());
    scrollBar->setMargin(0);
    scrollBar->update(true);
    scrollBar->setMinHeight(30);

    QVBoxLayout *layout = new QVBoxLayout(scroll);
    layout->setSpacing(0);
    layout->setMargin(8);
    label = new QLabel;
    label->setWordWrap(true);
    label->setObjectName("DetailInfo");
    label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(label, 0, Qt::AlignVCenter | Qt::AlignTop);
    setContent(bg);
}

void DetailWidget::setData(DataOrder *data)
{
//    if(!data) return;
//    QString m_Status = data->getStatuses().m_Status;
//    QString m_CustomerFirstName = data->getCustomerFirstName();
//    QString m_CustomerLastName = data->getCustomerLastName();
//    QString m_PaymentMethod = data->getPaymentMethod();
//    QString m_Remarks = data->getRemarks();
//    QString m_DeliveryInfo = data->getDeliveryInfo();
//    QString m_Price = data->getPrice();
//    QString m_GiftMessage = data->getGiftMessage();
//    QString m_VoucherCode = data->getVoucherCode();
//    QString m_CreatedAt = data->getCreatedAt();
//    QString m_UpdatedAt = data->getUpdatedAt();
//    QString m_NationalRegistrationNumber = data->getNationalRegistrationNumber();
//    QString m_PromisedShippingTimes = data->getPromisedShippingTimes();
//    QString m_ExtraAttributes = data->getExtraAttributes();
//    qint64 m_OrderNumber = data->getOrderNumber();
//    qint64 m_OrderId = data->getOrderNumber();
//    bool m_GiftOption = data->getGiftOption();
//    int m_ItemsCount = data->getItemsCount();
//    int m_Voucher = data->getVoucher();
//    int m_ShippingFee = data->getShippingFee();

//    QString m_FirstNameBilling = data->AddressBilling().m_FirstName;
//    QString m_LastNameBilling = data->AddressBilling().m_LastName;
//    QString m_PhoneBilling = data->AddressBilling().m_Phone;
//    QString m_Phone2Billing = data->AddressBilling().m_Phone2;
//    QString m_Address1Billing = data->AddressBilling().m_Address1;
//    QString m_Address2Billing = data->AddressBilling().m_Address2;
//    QString m_Address3Billing = data->AddressBilling().m_Address3;
//    QString m_Address4Billing = data->AddressBilling().m_Address4;
//    QString m_Address5Billing = data->AddressBilling().m_Address5;
//    QString m_CustomerEmailBilling = data->AddressBilling().m_CustomerEmail;
//    QString m_CityBilling = data->AddressBilling().m_City;
//    QString m_PostCodeBilling = data->AddressBilling().m_PostCode;
//    QString m_CountryBilling = data->AddressBilling().m_Country;

//    QString m_FirstNameShipping = data->AddressShipping().m_FirstName;
//    QString m_LastNameShipping = data->AddressShipping().m_LastName;
//    QString m_PhoneShipping = data->AddressShipping().m_Phone;
//    QString m_Phone2Shipping = data->AddressShipping().m_Phone2;
//    QString m_Address1Shipping = data->AddressShipping().m_Address1;
//    QString m_Address2Shipping = data->AddressShipping().m_Address2;
//    QString m_Address3Shipping = data->AddressShipping().m_Address3;
//    QString m_Address4Shipping = data->AddressShipping().m_Address4;
//    QString m_Address5Shipping = data->AddressShipping().m_Address5;
//    QString m_CustomerEmailShipping = data->AddressShipping().m_CustomerEmail;
//    QString m_CityShipping = data->AddressShipping().m_City;
//    QString m_PostCodeShipping = data->AddressShipping().m_PostCode;
//    QString m_CountryShipping = data->AddressShipping().m_Country;

//    QString result = "";
////    result.append(QString("Họ: %1").arg(m_CustomerLastName));
//    result.append(QString("Tên: %1").arg(m_CustomerFirstName));
//    result.append(QString("\nĐịa chỉ: %1").arg(m_Address1Shipping));
//    result.append(QString("\nQuốc gia: %1").arg(m_CountryShipping));
//    result.append(QString("\nTỉnh/Thành phố: %1").arg(m_Address3Shipping));
//    result.append(QString("\nQuận/Huyện: %1").arg(m_Address4Shipping));
//    result.append(QString("\nXã/Phường: %1").arg(m_Address5Shipping));
//    result.append(QString("\nSố điện thoại: %1").arg(m_PhoneShipping));
//    result.append(QString("\nEmail: %1").arg(m_CustomerEmailShipping));
//    result.append(QString("\nSố hóa đơn: %1").arg(m_OrderNumber));
//    result.append(QString("\nGiá: %1 (VND)").arg(m_Price));
//    result.append(QString("\nPhương thức thanh toán: %1").arg(m_PaymentMethod));
//    result.append(QString("\nNgày lập hóa đơn: %1").arg(m_CreatedAt));
//    result.append(QString("\nNgày cập nhật hóa đơn: %1").arg(m_UpdatedAt));
//    result.append(QString("\nSố lượng: %1").arg(m_ItemsCount));
//    result.append(QString("\nTrạng thái: %1").arg(m_Status));
//    result.append(QString("\nPhí vận chuyển: %1").arg(m_ShippingFee));

//    label->setText(result);
}

void DetailWidget::onScrollValueChanged(int value)
{
    scrollBar->setValue(value);
}
