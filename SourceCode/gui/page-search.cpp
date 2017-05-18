#include "page-search.h"
#include "CustomControl/page-navigation.h"
//#include "CustomControl/stable-view.h"
#include "CustomControl/stableview.h"
#include "CustomControl/sfilter-info.h"
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


#define MAX_RESULT 50
PageSearch::PageSearch(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(8);
    mainLayout->setMargin(0);

    QHBoxLayout *searchLayout = new QHBoxLayout(this);
    searchLayout->setSpacing(8);
    searchLayout->setMargin(0);

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

    resultFrame = new QFrame(this);
    resultFrame->installEventFilter(this);
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(filterInfo);
    mainLayout->addWidget(pageNavigation);
    mainLayout->addWidget(resultFrame, 1);

    /*Model*/
    model = new QStandardItemModel;
    readData();
    tableView = new STableView(resultFrame);
    tableView->setModel(model);
    tableView->show();

//    qmlTableView = new STableView;
//    qmlTableView->show();

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

void PageSearch::onSearch()
{


}

void PageSearch::onJumping(int page)
{
    if(page < 1) return;
    QStandardItem *newItem=0;
    int listLen = qMin(testList.length() - (page-1)*MAX_RESULT, MAX_RESULT);
    model->clear();
    model->setHorizontalHeaderLabels(header);
    for(int row = 0; row < listLen; row++){
        QStringList line = testList.at(row + (page-1)*MAX_RESULT).simplified().split(",");
        for(int col = 0; col < line.length(); col++) {
            newItem = new QStandardItem(line.at(col));
            model->setItem(row, col, newItem);
        }
    }
}

void PageSearch::readData()
{
    QFile file("D://example//TestTable//grades.txt");
    testList.clear();
    if (file.open(QFile::ReadOnly)) {
          QString line = file.readLine(200);
          header = line.simplified().split(",");
          while(file.canReadLine()){
                line = file.readLine(200);
                if(!line.startsWith("#") && line.contains(",")){
                      testList.append(line);
                }
          }
    }
    file.close();
    int listLen = testList.length();
    int numPage = listLen/MAX_RESULT + ((listLen%MAX_RESULT > 0) ? 1 : 0);
    pageNavigation->setRange(1,numPage,4);
    onJumping(1);
}
