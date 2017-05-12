#include "page-search.h"
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

PageSearch::PageSearch(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    QHBoxLayout *searchLayout = new QHBoxLayout(this);
    searchLayout->setSpacing(0);
    searchLayout->setMargin(0);

    searchLineEdit = new QLineEdit(this);
    searchButton = new QPushButton("Search", this);
    searchButton->setFixedSize(100, 20);
    connect(searchButton, &QPushButton::clicked, this, &PageSearch::onSearch);
    searchLayout->addWidget(searchLineEdit, 1);
    searchLayout->addWidget(searchButton, 0, Qt::AlignRight);

    resultFrame = new QFrame(this);
    resultFrame->installEventFilter(this);;
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(resultFrame, 1);

    /*Model*/
    model = new QStandardItemModel;
    readData();
    tableView = new QTableView(resultFrame);
    tableView->setModel(model);
    tableView->show();
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
    //testing
    QStandardItem *item = new QStandardItem;
    int row = model->rowCount();
    item->setText(QString("KHA TEST"));
    model->setItem(row, 0, item);
}

void PageSearch::readData()
{
    QFile file("D://example//TestTable//grades.txt");
    QString line;
    QStringList list;
    if (file.open(QFile::ReadOnly)) {
          line = file.readLine(200);
          list= line.simplified().split(",");
          model->setHorizontalHeaderLabels(list);

          int row=0;
          QStandardItem *newItem=0;
          while(file.canReadLine()){
                line = file.readLine(200);
                if(!line.startsWith("#") && line.contains(",")){
                      list= line.simplified().split(",");
                      for(int col=0; col<list.length(); col++){
                            newItem = new QStandardItem(list.at(col));
                            model->setItem(row ,col, newItem);
                      }
                      row++;
                }
          }
    }
    file.close();
}
