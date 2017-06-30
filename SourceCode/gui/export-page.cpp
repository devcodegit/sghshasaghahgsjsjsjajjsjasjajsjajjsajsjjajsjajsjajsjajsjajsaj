#include "export-page.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>

#define MIN_WIDTH 400
#define MIN_HEIGHT 250

ExportPage::ExportPage(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(8);
    mainLayout->setMargin(0);

    QGridLayout *editLayout = new QGridLayout;
    editLayout->setSpacing(8);
    editLayout->setMargin(8);

    QLabel *lbl1 = new QLabel("XUẤT HÀNG");
    QLabel *lbl2 = new QLabel("Mã hàng");
    QLabel *lbl3 = new QLabel("Sản phẩm");
    QLabel *lbl4 = new QLabel("Số đơn hàng");
    QLabel *lbl5 = new QLabel("Tên khách hàng");
    QLabel *lbl6 = new QLabel("Địa chỉ giao hàng");

    lineMaHang = new QLineEdit;
    lineSanPham = new QLineEdit;
    lineSoDonHang = new QLineEdit;
    lineTenKhachHang = new QLineEdit;
    lineDiaChiGiaoHang = new QLineEdit;

    QPushButton *btnOk = new QPushButton("Nhập");
    connect(btnOk, SIGNAL(clicked(bool)), this, SLOT(onOk()));
    QPushButton *btnCancel = new QPushButton("Bỏ qua");
    connect(btnCancel, SIGNAL(clicked(bool)), this, SLOT(onCancel()));
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setAlignment(Qt::AlignHCenter);
    btnLayout->addWidget(btnOk, 0, Qt::AlignHCenter);
    btnLayout->addWidget(btnCancel, 0, Qt::AlignHCenter);

    QFrame *tableFrame = new QFrame;
    tableFrame->setStyleSheet("border: 1px dashed blue;");


    editLayout->addWidget(lbl2, 0, 0, 1, 1);
    editLayout->addWidget(lineMaHang, 0, 1, 1, 3);
    editLayout->addWidget(lbl3, 1, 0, 1, 1);
    editLayout->addWidget(lineSanPham, 1, 1, 1, 1);
    editLayout->addWidget(lbl4, 1, 2, 1, 1);
    editLayout->addWidget(lineSoDonHang, 1, 3, 1, 1);
    editLayout->addWidget(lbl5, 2, 0, 1, 1);
    editLayout->addWidget(lineTenKhachHang, 2, 1, 1, 1);
    editLayout->addWidget(lbl6, 2, 2, 1, 1);
    editLayout->addWidget(lineDiaChiGiaoHang, 2, 3, 1, 1);

    mainLayout->addWidget(lbl1, 0, Qt::AlignHCenter);
    mainLayout->addLayout(editLayout);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(tableFrame, 1);

}

void ExportPage::onOk()
{

}

void ExportPage::onCancel()
{
    close();
}
