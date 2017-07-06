#include "page-search.h"
#include "table-model.h"
#include "export-page.h"
#include "../lazada/dataitem/lazada_data_item_order.h"
#include "../lazada/dataitem/lazada_data_item_list_order.h"
#include "../ui_executor.h"
#include "../uiconst.h"
#include "../uimodel.h"
#include "CustomControl/page-navigation.h"
//#include "CustomControl/stable-view.h"
#include "CustomControl/stableview.h"
#include "CustomControl/sfilter-info.h"
#include "CustomControl/detailwidget.h"
#include "CustomControl/date-range-widget.h"
#include "CustomControl/calendar-widget.h"
#include "CustomControl/toolbutton.h"
#include "CustomControl/loading-control.h"
#include "switch-bills-state-page.h"

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
#include <QResizeEvent>
#include <QApplication>
#include <QToolButton>
#include <QMenu>
#include <QAction>

using namespace Core::DataItem;
#define MAX_RESULT 60
PageSearch::PageSearch(QWidget *parent) : QFrame(parent)
{
    listItem = Lazada::Controls::LazadaHandler::instance()->getAllDataOrders(this);

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
    connect(dateRange, SIGNAL(choose(bool,QDate)), this, SLOT(onShowCalendar(bool,QDate)));
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
    filterInfo->hide();

    QHBoxLayout *btnLayout = new QHBoxLayout;

    btnChangeState = new ToolButton;
    QMenu *changeStateMenu = new QMenu;
    actionReady = new QAction("Sẵn sàng giao nhận", this);
    connect(actionReady, SIGNAL(triggered(bool)), this, SLOT(onReadyChangeState()));
    actionCancel = new QAction("Hủy", this);
    connect(actionCancel, SIGNAL(triggered(bool)), this, SLOT(onCancelChangeState()));
    changeStateMenu->addAction(actionReady);
    changeStateMenu->addAction(actionCancel);
    btnChangeState->setMenu(changeStateMenu);
    btnChangeState->setDefaultAction(actionReady);

    btnExport = new ToolButton;
    QMenu *exportMenu = new QMenu;
    actionCsvFileExport = new QAction("Xuất file .CSV", this);
    connect(actionCsvFileExport, SIGNAL(triggered(bool)), this, SLOT(onCsv()));
    actionPrint = new QAction("In", this);
    connect(actionPrint, SIGNAL(triggered(bool)), this, SLOT(onPrint()));
    exportMenu->addAction(actionCsvFileExport);
    exportMenu->addAction(actionPrint);
    btnExport->setMenu(exportMenu);
    btnExport->setDefaultAction(actionCsvFileExport);

    btnLayout->addWidget(btnChangeState, 0, Qt::AlignLeft);
    btnLayout->addWidget(btnExport, 0, Qt::AlignRight);

    resultFrame = new QFrame(this);
    resultFrame->installEventFilter(this);
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(filterInfo, 0);
    mainLayout->addWidget(pageNavigation);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(resultFrame, 1);

    tableView = new STableView(resultFrame);
    tableView->setModel(TableModel::instance()->getModel(TableModel::TABLE_MAIN));
    tableView->show();
    connect(tableView, SIGNAL(itemClicked(int,int)), this, SLOT(onShowInfo(int,int)));
    connect(tableView, SIGNAL(updateCheckbox(int,int,bool)), this, SLOT(onUpdateCheckbox(int,int,bool)));

    checkUpdateTimer.setInterval(1000);
    connect(&checkUpdateTimer, SIGNAL(timeout()), this, SLOT(onCheckUpdateData()));
    checkUpdateTimer.start();

    if(!loading) loading = new LoadingControl(20, 20, true, resultFrame);
    loading->showLoading();

    SwitchBillsStatePage *page = new SwitchBillsStatePage;
    page->show();

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
            if(loading) loading->showLoading();
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

void PageSearch::navigate(PageSearch::PAGE page)
{
    switch(page) {
    case ALL:
        allItems();
        break;
    case PROCESSING:
        processingItems();
        break;
    case READY:
        readyItems();
        break;
    case TRANSMITTING:
        transmittingItems();
        break;
    case DONE:
        doneItems();
        break;
    default: break;
    }
}

bool PageSearch::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress) {
        QRect rect = QRect(calendarWidget->mapToGlobal(QPoint(0,0)), QSize(calendarWidget->size()));
        if(!rect.contains(QCursor::pos())) {
            calendarWidget->close();
            qApp->removeEventFilter(this);
        }
    }
    if(object == resultFrame) {
        if(event->type() == QEvent::Resize) {
            //table->setFixedSize(resultFrame->size() - QSize(0, 50));
            tableView->setFixedSize(resultFrame->size() - QSize(0, 50));
        }
    }
    return QFrame::eventFilter(object, event);
}

void PageSearch::showEvent(QShowEvent *)
{
}

void PageSearch::resizeEvent(QResizeEvent *event)
{

}

void PageSearch::onSearch()
{
    qDebug () << "onSearch" << filterInfo->getFilterList();
}

void PageSearch::onJumping(int page)
{
    if(page < 1) return;
    if(loading) {
        loading->hideLoading();
    }
    currentPage = page;
    qDebug () << "onJumping" << page;
    int listLen = qMin(linesList.length() - (page-1)*MAX_RESULT, MAX_RESULT);
    TableModel::instance()->setHorizontalHeaderLabels(UIModel::instance()->getDataTableHeader(), TableModel::TABLE_MAIN);
    for(int row = 0; row < listLen; row++){
        QStringList line = linesList.at(row + (page-1)*MAX_RESULT).simplified().split("{}");
        TableModel::instance()->pushItem(line, TableModel::TABLE_MAIN);
    }
}

void PageSearch::onShowInfo(int row, int col)
{
    if(!infoDialog) {
        infoDialog = new DetailWidget;
    }
    int index = row + (currentPage - 1) * MAX_RESULT;
    infoDialog->setParent(UIModel::instance()->getMainWindow());
    infoDialog->setData(listItem.at(index));
    infoDialog->show();
    infoDialog->setFocus();
}

void PageSearch::onUpdateCheckbox(int row, int col, bool val)
{
    qDebug () << "onUpdateCheckbox();" << row << col << val;
    TableModel::instance()->updateModel(row, col, QVariant(val), TableModel::TABLE_MAIN);
}

void PageSearch::onCheckUpdateData()
{
    if(needUpdate) {
        readData();
        needUpdate = false;
    }
}

void PageSearch::onAddFilterItem(QDate date)
{
    if(isStartClicked) {
        filterInfo->addItem(QString("Từ ngày: %1").arg(date.toString("dd/MM/yyyy")), SFilterInfo::ID_START_DATE);
        dateRange->setStartDate(date);
    }
    else {
        filterInfo->addItem(QString("Đến ngày: %1").arg(date.toString("dd/MM/yyyy")), SFilterInfo::ID_END_DATE);
        dateRange->setEndDate(date);
    }
    filterInfo->show();
}

void PageSearch::onShowCalendar(bool isStart, QDate date)
{
    QWidget * w = (QWidget*)sender();
    if(!calendarWidget) {
        calendarWidget = new CalendarWidget(this);
        calendarWidget->installEventFilter(this);
        connect(calendarWidget, SIGNAL(clicked(QDate)), this, SLOT(onAddFilterItem(QDate)));
    }
    calendarWidget->move(w->x() - 44, w->y() + w->height());
    calendarWidget->show();
    calendarWidget->raise();
    calendarWidget->setFocus();
    qApp->installEventFilter(this);
    isStartClicked = isStart;
}

void PageSearch::onReadyChangeState()
{
    qDebug() << "ready";
    btnChangeState->setDefaultAction(actionReady);
    pushReadyData();
}

void PageSearch::onCancelChangeState()
{
    qDebug () << "cancel";
    btnChangeState->setDefaultAction(actionCancel);
}

void PageSearch::onExport()
{
    ExportPage *p = new ExportPage;
    p->show();
}

void PageSearch::onPrint()
{
    qDebug() << "print";
    btnExport->setDefaultAction(actionPrint);
}

void PageSearch::onCsv()
{
    qDebug() << "csv";
    btnExport->setDefaultAction(actionCsvFileExport);
}

void PageSearch::readData()
{
    linesList.clear();
    for(int i = 0; i < listItem.length(); i++) {
        QString no_order = QString::number(listItem.at(i)->OrderId());
        QString date_order = listItem.at(i)->getCreatedAt();
        QString waiting_queue = "";
        QString payment_method = listItem.at(i)->getPaymentMethod();
        QString price = listItem.at(i)->getPrice();
        int num = listItem.at(i)->getItemsCount();
        QString status = listItem.at(i)->getStatuses().m_Status;
        QString printed = QString("true");
        QString action = listItem.at(i)->getDeliveryInfo();
        QString line = QString("[]{}Hóa đơn{}%1{}%2{}%3{}%4{}%5{}%6{}%7{}%8{}%9").arg(no_order, date_order, waiting_queue, payment_method, price, QString::number(num), status, printed, action);
        linesList.append(line);
        mapItems.insert(listItem.at(i)->OrderId(), listItem.at(i));

    }
    int listLen = listItem.length();
    if(listLen <= 0) return;
    int numPage = listLen/MAX_RESULT + ((listLen%MAX_RESULT > 0) ? 1 : 0);
    pageNavigation->setRange(1,numPage,4);
    qDebug () << "onJumping from start";
    onJumping(1);
}

void PageSearch::preloadData()
{
}

void PageSearch::pushReadyData()
{
    TableModel::instance()->getModel(TableModel::TABLE_EXPORT)->clear();
    TableModel::instance()->setHorizontalHeaderLabels(UIModel::instance()->getExportTableHeader(), TableModel::TABLE_EXPORT);
    QStandardItemModel *model = TableModel::instance()->getModel(TableModel::TABLE_MAIN);
    for(int i = 0; i < model->rowCount(); i++) {
        QStandardItem *item = model->item(i, 0);
        if(item) {
            bool isChecked = item->data(Qt::EditRole).toBool();
            if(isChecked) {
                int billNo = model->item(i, 2)->data(Qt::DisplayRole).toInt();
                LazadaDataItemOrder *order = mapItems.value(billNo, 0);
                if(order) {
                    QString provider = "";
                    QString transCode = "";
                    int orderedNo = order->getOrderNumber();
                    TableModel::instance()->pushItem(QStringList() << QString::number(billNo) << "1/1" << provider << transCode << QString::number(orderedNo), TableModel::TABLE_EXPORT);
                }
            }
        }
    }
}

void PageSearch::allItems()
{
    tableView->setModel(TableModel::instance()->getModel(TableModel::TABLE_MAIN));
}

void PageSearch::processingItems()
{

}

void PageSearch::readyItems()
{
    tableView->setModel(TableModel::instance()->getModel(TableModel::TABLE_READY));
}

void PageSearch::transmittingItems()
{

}

void PageSearch::doneItems()
{

}
