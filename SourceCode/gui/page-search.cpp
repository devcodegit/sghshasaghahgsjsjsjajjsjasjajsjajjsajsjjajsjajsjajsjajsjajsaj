#include "page-search.h"
#include "CustomControl/page-navigation.h"
//#include "CustomControl/stable-view.h"
#include "CustomControl/stableview.h"
#include "CustomControl/sfilter-info.h"
#include "CustomControl/detailwidget.h"
#include "../uimodel.h"
#include "table-model.h"
#include "../lazada/dataitem/lazada_data_item_order.h"
#include "../lazada/dataitem/lazada_data_item_list_order.h"
#include "../ui_executor.h"

#include <QScrollArea>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QEvent>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QFile>
#include <QDebug>
#include <QVariant>

using namespace Core::DataItem;
#define MAX_RESULT 50
PageSearch::PageSearch(QWidget *parent) : QWidget(parent)
{
    listItem = Lazada::Controls::LazadaHandler::instance()->getAllDataOrders(this);
    header = UIModel::instance()->getDataTableHeader();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(8);
    mainLayout->setMargin(0);

    QHBoxLayout *searchLayout = new QHBoxLayout(this);
    searchLayout->setSpacing(8);
    searchLayout->setMargin(8);

    line1 = new QLineEdit(this);
    line1->setPlaceholderText("Số đơn hàng");
    line2 = new QLineEdit(this);
    line2->setPlaceholderText("Khách hàng");
    line3 = new QLineEdit(this);
    line3->setPlaceholderText("Sản phẩm");
    line4 = new QLineEdit(this);
    line4->setPlaceholderText("Thanh toán");
    searchButton = new QPushButton("Tìm kiếm", this);
    searchButton->setFixedSize(100, 20);
    connect(searchButton, &QPushButton::clicked, this, &PageSearch::onSearch);
    searchLayout->addWidget(line1, 1);
    searchLayout->addWidget(line2, 1);
    searchLayout->addWidget(line3, 1);
    searchLayout->addWidget(line4, 1);
    searchLayout->addWidget(searchButton, 0, Qt::AlignRight);

    pageNavigation = new PageNavigation(this);
    connect(pageNavigation, &PageNavigation::jumping, this, &PageSearch::onJumping);


    filterInfo = new SFilterInfo;
    for(int i = 0; i < 100; i++) {
        filterInfo->addItem(QString("Item %1").arg(i));
    }
    filterInfo->hide();

    resultFrame = new QFrame(this);
    resultFrame->installEventFilter(this);
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(filterInfo);
    mainLayout->addWidget(pageNavigation);
    mainLayout->addWidget(resultFrame, 1);

    /*Model*/
    model = TableModel::instance()->getModel();
    tableView = new STableView(resultFrame);
    tableView->setModel(model);
    tableView->show();
    connect(tableView, SIGNAL(itemClicked(int,int)), this, SLOT(onShowInfo(int,int)));

//    qmlTableView = new STableView;
//    qmlTableView->show();


    checkUpdateTimer.setInterval(1000);
    connect(&checkUpdateTimer, SIGNAL(timeout()), this, SLOT(onCheckUpdateData()));
    checkUpdateTimer.start();

}

void PageSearch::OnRequestCompleted(ResponseResult *result)
{
    if (result)
    {
        int requestType = result->getRequestType();
        QString errorMsg = result->getErrorMsg();

        UIExecutor::invoke([&, requestType, errorMsg]()
        {
            //Kha todo:
            listItem = Lazada::Controls::LazadaHandler::instance()->getAllDataOrders(this);
            qDebug () << "OnRequestCompleted();" << requestType << errorMsg << listItem.length();
            needUpdate = true;
        });
    }
}

void PageSearch::OnRequestFailed(ResponseResult *result)
{
    if (result)
    {
        int requestType = result->getRequestType();
        QString errorMsg = result->getErrorMsg();

        UIExecutor::invoke([&, requestType, errorMsg]()
        {
            //Kha todo:

        });
    }
}

bool PageSearch::eventFilter(QObject *object, QEvent *event)
{
    if(object == resultFrame) {
        if(event->type() == QEvent::Resize) {
            tableView->setFixedSize(resultFrame->size() - QSize(0, 40));
        }
    }
    return QWidget::eventFilter(object, event);
}

void PageSearch::showEvent(QShowEvent *)
{
}

void PageSearch::onSearch()
{
    if(tableView) {

    }
}

void PageSearch::onJumping(int page)
{
    if(page < 1) return;
    currentPage = page;
    int listLen = qMin(linesList.length() - (page-1)*MAX_RESULT, MAX_RESULT);
    model->clear();
    model->setHorizontalHeaderLabels(header);
    for(int row = 0; row < listLen; row++){
        QStringList line = linesList.at(row + (page-1)*MAX_RESULT).simplified().split("{}");
        TableModel::instance()->pushItem(line);
    }
}

void PageSearch::onShowInfo(int row, int col)
{
    if(!infoDialog) infoDialog = new DetailWidget;
    int index = row + (currentPage - 1) * MAX_RESULT;
    infoDialog->setParent(UIModel::instance()->getMainWindow());
    infoDialog->setData(listItem.at(index));
    infoDialog->show();
    infoDialog->setFocus();
}

void PageSearch::onCheckUpdateData()
{
    if(needUpdate) {
        readData();
        needUpdate = false;
    }
}

void PageSearch::readData()
{
    linesList.clear();
    for(int i = 0; i < listItem.length(); i++) {
        QString no_order = QString::number(listItem.at(i)->getOrderNumber());
        QString date_order = listItem.at(i)->getCreatedAt();
        QString waiting_queue = "";
        QString payment_method = listItem.at(i)->getPaymentMethod();
        QString price = listItem.at(i)->getPrice();
        int num = listItem.at(i)->getItemsCount();
        QString status = listItem.at(i)->getStatuses().m_Status;
        QString printed = QString("true");
        QString action = listItem.at(i)->getDeliveryInfo();
        QString line = QString("Hóa đơn{}%1{}%2{}%3{}%4{}%5{}%6{}%7{}%8{}%9").arg(no_order, date_order, waiting_queue, payment_method, price, QString::number(num), status, printed, action);
        linesList.append(line);
    }
    int listLen = linesList.length();
    if(listLen <= 0) return;
    int numPage = listLen/MAX_RESULT + ((listLen%MAX_RESULT > 0) ? 1 : 0);
    pageNavigation->setRange(1,numPage,4);
    onJumping(1);
}

void PageSearch::preloadData()
{
}
