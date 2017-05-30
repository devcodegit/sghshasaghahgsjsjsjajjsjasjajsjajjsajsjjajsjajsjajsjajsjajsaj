#include "stabwidget.h"
#include <QBoxLayout>
#include <QFrame>
#include <QScrollArea>
#include <QLabel>
#include <QResizeEvent>
#include <QEvent>
#include <QScrollBar>
#include <QDebug>

#define TAB_HEIGHT 30
#define CONTENT_MIN_SIZE 300

STabWidget::STabWidget(QWidget *parent) : QWidget(parent)
{
    tabFrame = new QFrame(this);
    tabFrame->installEventFilter(this);
    tabFrame->setFixedHeight(TAB_HEIGHT + 2);
    tabFrame->move(0,0);

    tab = new QFrame(tabFrame);
    tab->setFixedHeight(TAB_HEIGHT);
    tab->move(0,0);
    tabLayout = new QHBoxLayout(tab);
    tabLayout->setSpacing(3);
    tabLayout->setMargin(0);
    tabLayout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    tabScrollArea = new QScrollArea(tabFrame);
    tabScrollArea->setObjectName("TransWg");
    tabScrollArea->setContentsMargins(0,0,0,0);
    tabScrollArea->setFocusPolicy(Qt::NoFocus);
    tabScrollArea->setWidget(tab);
    tabScrollArea->setFixedHeight(tabFrame->height());
    tabScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tabScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tabScrollArea->setWidgetResizable(true);
    tabScrollArea->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
}

void STabWidget::addItem(const QString &title, QWidget *contentWg)
{
    QFrame *frame = new QFrame(tab);
    frame->installEventFilter(this);
    frame->setObjectName("TabButton");
    frame->setContentsMargins(8,8,8,8);
    QLabel *tabLbl = new QLabel(title, frame);
    tabLbl->setObjectName("TabLbl");
    tabLbl->setAlignment(Qt::AlignCenter);
    tabLbl->adjustSize();
    tabLayout->addWidget(frame, 0, Qt::AlignVCenter | Qt::AlignLeft);
    frame->setFixedSize(tabLbl->fontMetrics().width(title) + 16, tab->height());
    tabLbl->move((frame->width() - tabLbl->width())/2, (frame->height() - tabLbl->height())/2);
    if(!contentFrame) {
        contentFrame = new QFrame(this);
        contentFrame->setMinimumSize(CONTENT_MIN_SIZE, CONTENT_MIN_SIZE);
        contentFrame->move(0, tabFrame->height());
    }
    contentWg->setParent(contentFrame);
    contentWg->hide();
    mapTabContent.insert(frame, contentWg);
}

void STabWidget::resizeEvent(QResizeEvent *event)
{
    tabFrame->setFixedWidth(event->size().width());
    tabScrollArea->setFixedWidth(tabFrame->width());
    if(contentFrame) contentFrame->setFixedSize(event->size().width(), event->size().height() - tabFrame->height());
}

bool STabWidget::eventFilter(QObject *object, QEvent *event)
{
    if(object == tabFrame) {
        if(event->type() == QEvent::Wheel) {
            QWheelEvent *ev = (QWheelEvent*)event;
            tabScrollArea->horizontalScrollBar()->setValue(tabScrollArea->horizontalScrollBar()->value() + (ev->delta() > 0 ? - 50 : 50));
        }
    }
    else if(mapTabContent.contains((QFrame*)object)) {
        if(event->type() == QEvent::MouseButtonRelease) {
            showTab((QFrame*)object);
        }
    }
    return QWidget::eventFilter(object, event);
}

void STabWidget::showEvent(QShowEvent *)
{
    showTab(mapTabContent.firstKey());
}

void STabWidget::onScroll(int value)
{
    Q_UNUSED(value);
}

void STabWidget::showTab(QFrame *tab)
{
    if(!tab) return;
    QWidget *content = mapTabContent.value(tab, 0);
    if(!content && currentContent == content) return;
    if(currentContent) currentContent->hide();
    currentContent = content;
    if(content->isHidden()) {
        content->show();
        content->raise();
    }
}
