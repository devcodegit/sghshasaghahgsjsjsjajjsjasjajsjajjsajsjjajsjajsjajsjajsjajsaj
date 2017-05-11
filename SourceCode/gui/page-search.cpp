#include "page-search.h"
#include <QScrollArea>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QEvent>

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
    searchLayout->addWidget(searchLineEdit, 1);
    searchLayout->addWidget(searchButton, 0, Qt::AlignRight);

    resultFrame = new QFrame(this);
    resultFrame->installEventFilter(this);;
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(resultFrame, 1);

    contentResult = new QFrame(resultFrame);
    contentResult->setFixedSize(1000, 1000);
    contentResult->setStyleSheet("border: 5px solid red; border-radius: 10px;");
    resultArea = new QScrollArea(resultFrame);
    resultArea->setObjectName("TransWg");
    resultArea->setContentsMargins(0,0,0,0);
    resultArea->setFocusPolicy(Qt::NoFocus);
    resultArea->setWidget(contentResult);
//    resultArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    resultArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    resultArea->setWidgetResizable(true);
    resultArea->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    resultArea->move(0,0);
    resultArea->show();
    resultArea->raise();
}

bool PageSearch::eventFilter(QObject *object, QEvent *event)
{
    if(object == resultFrame) {
        if(event->type() == QEvent::Resize) {
            resultArea->resize(resultFrame->size() - QSize(0,40));
        }
    }
    return QWidget::eventFilter(object, event);
}
