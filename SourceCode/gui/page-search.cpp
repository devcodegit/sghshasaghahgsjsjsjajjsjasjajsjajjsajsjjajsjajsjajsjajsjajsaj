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
#include "CustomControl/date-range-widget.h"
#include "CustomControl/table/tinytablewidget.h"

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
#define MAX_RESULT 30
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
    dateRange = new DateRangeWidget(this);
    searchButton = new QPushButton("Tìm kiếm", this);
    searchButton->setFixedSize(100, 20);
    connect(searchButton, &QPushButton::clicked, this, &PageSearch::onSearch);
    searchLayout->addWidget(line1, 1);
    searchLayout->addWidget(line2, 1);
    searchLayout->addWidget(line3, 1);
    searchLayout->addWidget(dateRange, 1);
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


    checkUpdateTimer.setInterval(1000);
    connect(&checkUpdateTimer, SIGNAL(timeout()), this, SLOT(onCheckUpdateData()));
    checkUpdateTimer.start();

    table = new TinyTableWidget(resultFrame);
    table->show();
    dataHandler = new DataHandler;
    dataHandler->setMaxRowPerPage(MAX_RESULT);
    table->setHeader(UIModel::instance()->getDataTableHeader());
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
            table->setFixedSize(resultFrame->size() - QSize(0, 50));

        }
    }
    return QWidget::eventFilter(object, event);
}

void PageSearch::showEvent(QShowEvent *)
{
}

void PageSearch::onSearch()
{
}

void PageSearch::onJumping(int page)
{
    if(page < 1) return;
    currentPage = page;
    table->setData(dataHandler->getData(page));
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

        QList<DataHandler::data_handler *> row;
        row.append(new DataHandler::data_handler(i, i, 0, DataHandler::PLAINTEXT, "Hóa Đơn", "", false, QMap<int, QString>(), -1));
        row.append(new DataHandler::data_handler(i, i, 0, DataHandler::PLAINTEXT, no_order, "", false, QMap<int, QString>(), -1));
        row.append(new DataHandler::data_handler(i, i, 0, DataHandler::PLAINTEXT, date_order, "", false, QMap<int, QString>(), -1));
        row.append(new DataHandler::data_handler(i, i, 0, DataHandler::PLAINTEXT, waiting_queue, "", false, QMap<int, QString>(), -1));
        row.append(new DataHandler::data_handler(i, i, 0, DataHandler::PLAINTEXT, payment_method, "", false, QMap<int, QString>(), -1));
        row.append(new DataHandler::data_handler(i, i, 0, DataHandler::PLAINTEXT, price, "", false, QMap<int, QString>(), -1));
        row.append(new DataHandler::data_handler(i, i, 0, DataHandler::PLAINTEXT, QString::number(num), "", false, QMap<int, QString>(), -1));
        row.append(new DataHandler::data_handler(i, i, 0, DataHandler::PLAINTEXT, status, "", false, QMap<int, QString>(), -1));
        row.append(new DataHandler::data_handler(i, i, 0, DataHandler::PLAINTEXT, printed, "", false, QMap<int, QString>(), -1));
        row.append(new DataHandler::data_handler(i, i, 0, DataHandler::PLAINTEXT, action, "", false, QMap<int, QString>(), -1));
        dataHandler->addRow(row);
    }
    int listLen = listItem.length();
    if(listLen <= 0) return;
    int numPage = listLen/MAX_RESULT + ((listLen%MAX_RESULT > 0) ? 1 : 0);
    pageNavigation->setRange(1,numPage,4);
    onJumping(1);
}

void PageSearch::preloadData()
{
}
