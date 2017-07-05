#include "switch-bills-state-page.h"
#include "table-model.h"
#include "CustomControl/stableview.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QStandardItemModel>
#include <QStandardItem>

SwitchBillsStatePage::SwitchBillsStatePage(QWidget *parent) : QFrame(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(8);
    mainLayout->setMargin(8);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->setMargin(0);
    btnLayout->setSpacing(8);

    title = new QLabel;
    model = TableModel::instance()->getModel(TableModel::TABLE_EXPORT);
    tableView = new STableView;
    tableView->setModel(model);
    tableView->show();
    btnChange = new QPushButton("Thay đổi hình thức giao nhận");
    connect(btnChange, SIGNAL(clicked(bool)), this, SLOT(onChange()));
    btnClose = new QPushButton("Đóng");
    connect(btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    btnSave = new QPushButton;
    connect(btnSave, SIGNAL(clicked(bool)), this, SLOT(onSave()));
    btnAll = new QPushButton("Tất cả tài liệu");
    connect(btnAll, SIGNAL(clicked(bool)), this, SLOT(onAllDocs()));
    btnBill = new QPushButton("Hóa đơn");
    connect(btnBill, SIGNAL(clicked(bool)), this, SLOT(onBills()));
    btnStamp = new QPushButton("Tem gửi");
    connect(btnStamp, SIGNAL(clicked(bool)), this, SLOT(onStamp()));

    btnLayout->addWidget(btnChange, 0, Qt::AlignLeft);
    btnLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    btnLayout->addWidget(btnClose, 0, Qt::AlignRight);
    btnLayout->addWidget(btnAll, 0, Qt::AlignRight);
    btnLayout->addWidget(btnBill, 0, Qt::AlignRight);
    btnLayout->addWidget(btnStamp, 0, Qt::AlignRight);
    btnLayout->addWidget(btnSave, 0, Qt::AlignRight);

    mainLayout->addWidget(title);
    mainLayout->addWidget(tableView, 1);
    mainLayout->addLayout(btnLayout);

    setState(INIT);
}

void SwitchBillsStatePage::setState(int state)
{
    currentState = state;
    switch(state) {
    case INIT:
        uiStateInit();
        break;
    case PREVIEW:
        uiStatePreview();
        break;
    case READY:
        uiStateReady();
        break;
    default:
        break;
    }
}

void SwitchBillsStatePage::nextState()
{
    setState(currentState+1);
}

void SwitchBillsStatePage::onSave()
{
}

void SwitchBillsStatePage::onChange()
{

}

void SwitchBillsStatePage::onAllDocs()
{

}

void SwitchBillsStatePage::onBills()
{

}

void SwitchBillsStatePage::onStamp()
{

}

void SwitchBillsStatePage::uiStateInit()
{
    title->setText("Vui lòng nhập ID hóa đơn");
    btnSave->setText("Lưu hóa đơn");
    btnChange->show();
    btnClose->show();
    btnAll->hide();
    btnBill->hide();
    btnStamp->hide();
    btnSave->show();
}

void SwitchBillsStatePage::uiStatePreview()
{
    title->setText("Vui lòng nhập ID hóa đơn");
    btnSave->setText("Sẵn sàng giao hàng");
    btnChange->show();
    btnClose->show();
    btnAll->show();
    btnBill->show();
    btnStamp->show();
    btnSave->show();
}

void SwitchBillsStatePage::uiStateReady()
{
    title->setText("Đơn hàng sẵn sàng được giao");
    btnChange->hide();
    btnClose->show();
    btnAll->show();
    btnBill->show();
    btnStamp->show();
    btnSave->hide();
}
