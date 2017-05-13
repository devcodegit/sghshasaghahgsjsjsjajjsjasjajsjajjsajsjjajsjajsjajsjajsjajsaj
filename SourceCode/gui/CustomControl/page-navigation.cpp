#include "page-navigation.h"
#include "../../style-sheet-manager.h"
#include <QBoxLayout>
#include <QMouseEvent>
#include <QPushButton>
#include <QDebug>
#include <QPixmap>

#define ICON_SIZE 20

PageNavigation::PageNavigation(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(8);
    mainLayout->setMargin(0);
    mainLayout->setAlignment(Qt::AlignCenter);

    next = new PageItem(PageItem::NextNavigation, this);
    next->setToolTip("Trang sau");
    connect(next, SIGNAL(clicked()), this, SLOT(onNext()));
    prev = new PageItem(PageItem::PreviousNavigation, this);
    prev->setToolTip("Trang trước");
    connect(prev, SIGNAL(clicked()), this, SLOT(onPrev()));
    first = new PageItem(PageItem::FirstPageNavigation, this);
    first->setToolTip("Trang đầu");
    connect(first, SIGNAL(clicked()), this, SLOT(onFirstPage()));
    last = new PageItem(PageItem::LastPageNavigation, this);
    last->setToolTip("Trang cuối");
    connect(last, SIGNAL(clicked()), this, SLOT(onLastPage()));

    mainLayout->addWidget(first);
    mainLayout->addWidget(prev);
    mainLayout->addWidget(next);
    mainLayout->addWidget(last);
}

void PageNavigation::setCurrentPage(int page)
{
    onDirectingToPage(page);
}

void PageNavigation::setRange(int from, int to, int range)
{
    this->from = qMin(from, to);
    this->to = qMax(to, from);
    if(this->from < 1) this->from = 1;
    if(this->to < 1) this->to = 1;
    currentPage = this->from;
    if(range == -1) {
        this->maxViewRange = this->to - this->from + 1;
    }
    else this->maxViewRange = range;
    moveRange(this->from, qMin(this->from + maxViewRange - 1, this->to));
}

void PageNavigation::onDirectingToPage(int page)
{
    if(currentItem && currentItem->getId() != page) {
        currentItem->clearHighlight();
    }
    for(int i = 0; i < listItem.length(); i++) {
        if(listItem.at(i)->getId() == page) {
            currentItem = listItem.at(i);
            currentPage = page;
            currentItem->setHighlight();
            break;
        }
    }
}

void PageNavigation::onNext()
{
    if(listItem.isEmpty()) return;
    currentPage++;
    if(currentPage > to) {
        currentPage--;
        return;
    }
    else if(currentPage > (tempFrom + maxViewRange - 1)) {
        moveRange(qMin(currentPage, to - maxViewRange + 1), qMin(currentPage + maxViewRange - 1, to));
    }
    else {
        onDirectingToPage(currentPage);
    }
}

void PageNavigation::onPrev()
{
    if(listItem.isEmpty()) return;
    currentPage--;
    if(currentPage < from) {
        currentPage++;
        return;
    }
    else if(currentPage < tempFrom) {
        moveRange(qMax(currentPage - maxViewRange + 1, from), qMax(currentPage, from + maxViewRange - 1));
    }
    else {
        onDirectingToPage(currentPage);
    }
}

void PageNavigation::onFirstPage()
{
    if(listItem.isEmpty()) return;
    currentPage = from;
    moveRange(from, qMin(from + maxViewRange - 1, to));
    onDirectingToPage(from);
}

void PageNavigation::onLastPage()
{
    if(listItem.isEmpty()) return;
    currentPage = to;
    moveRange(qMax(to - maxViewRange + 1, from), to);
    onDirectingToPage(to);
}

void PageNavigation::moveRange(int from, int to)
{
    int _from, _to;
    _from = qMin(from, to);
    _to = qMax(from, to);
    if(_from < 1) _from = 1;
    if(_to < 1) _to = 1;
    tempFrom = _from;
    int len = listItem.length();
    int count = 0;
    for(int i = 0; i < len; i++) {
        listItem.at(i)->hide();
        listItem.at(i)->clearHighlight();
        listItem.at(i)->setId(-1);
    }
    for(int i = _from; i <= _to; i++, count++) {
        PageItem *item;
        if(count < len) {
            item = listItem.at(count);
        }
        else {
            item = new PageItem;
            connect(item, SIGNAL(clicked(int)), this, SLOT(onDirectingToPage(int)));
            mainLayout->insertWidget(2 + count, item);
            listItem.append(item);
        }
        item->setId(i);
        item->show();
    }
    currentItem = listItem.at(currentPage - from );
    currentItem->setHighlight();
}

PageItem::PageItem(Type type, QWidget *parent) : type(type), QLabel(parent)
{
    setObjectName("PageLbl");
    setAlignment(Qt::AlignCenter);
    setCursor(Qt::PointingHandCursor);
    if(type != Page) {
        setFixedSize(ICON_SIZE, ICON_SIZE);
        QPixmap icon;
        switch(type) {
        case NextNavigation:
            icon = QPixmap(":/Icon/Image/next.svg").scaled(ICON_SIZE, ICON_SIZE);
            break;
        case PreviousNavigation:
            icon = QPixmap(":/Icon/Image/previous.svg").scaled(ICON_SIZE, ICON_SIZE);
            break;
        case FirstPageNavigation:
            icon = QPixmap(":/Icon/Image/top.svg").scaled(ICON_SIZE, ICON_SIZE);
            break;
        case LastPageNavigation:
            icon = QPixmap(":/Icon/Image/last.svg").scaled(ICON_SIZE, ICON_SIZE);
            break;
        default:
            break;
        }
        setPixmap(icon);
    }
}

void PageItem::setId(int id)
{
    this->id = id;
    this->setText(QString::number(id));
}

int PageItem::getId()
{
    return this->id;
}

void PageItem::setHighlight()
{
    StyleSheetManager::changeProperty(this, "state", "highlight");
}

void PageItem::clearHighlight()
{
    StyleSheetManager::changeProperty(this, "state", "");
}

void PageItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        if(type == Page) {
            emit clicked(this->id);
            setHighlight();
        }
        else {
            emit clicked();
        }
    }
}
