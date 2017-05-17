#include "sfilter-info.h"
#include "flowlayout.h"
#include <QBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QSvgWidget>
#include <QEvent>
#include <QResizeEvent>
#include <QScrollArea>

SFilterInfo::SFilterInfo(QWidget *parent) : QWidget(parent)
{
    scroll = new QWidget;
    scroll->setObjectName("TransWg");
    filterItemLayout = new FlowLayout(scroll);
    scrollArea = new QScrollArea(this);
    scrollArea->setFocusPolicy(Qt::NoFocus);
    scrollArea->setWidget(scroll);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    setFixedHeight(50);
}

void SFilterInfo::addItem(const QString &title)
{
    FilterItem *item = getItem();
    item->show();
    item->setTitle(title);
    filterItemLayout->addWidget(item);
}

void SFilterInfo::resizeEvent(QResizeEvent *event)
{
    scrollArea->setFixedSize(event->size());
    scroll->setFixedWidth(event->size().width());
}

void SFilterInfo::onRemoveItem()
{
    filterItemLayout->removeWidget((QWidget*)sender());
}

FilterItem *SFilterInfo::getItem()
{
    for(int i = 0; i < listItems.length(); i++) {
        FilterItem *item = listItems.at(i);
        if(item && item->state() == FilterItem::NotUSING) {
            return item;
        }
    }
    FilterItem *item = new FilterItem(this);
    connect(item, SIGNAL(closeItem()), this, SLOT(onRemoveItem()));
    listItems.append(item);
    return item;
}

FilterItem::FilterItem(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(8);
    layout->setMargin(2);

    _title = new QLabel;
    _closeWg = new QSvgWidget;
    _closeWg->setFixedSize(12, 10);
    _closeWg->installEventFilter(this);
    _closeWg->setCursor(Qt::PointingHandCursor);
    _closeWg->load(QString(":/Icon/Image/frame_icon_close_hover_12x10_gray.svg"));

    layout->addWidget(_title, 0, Qt::AlignVCenter);
    layout->addWidget(_closeWg, 0, Qt::AlignVCenter);
}

void FilterItem::setTitle(const QString &title)
{
    _title->setText(title);
    _state = USING;
}

bool FilterItem::eventFilter(QObject *object, QEvent *event)
{
    if(object == _closeWg) {
        if(event->type() == QEvent::Enter) {
            _closeWg->load(QString(":/Icon/Image/frame_icon_close_12x10_white_hover.svg"));
        }
        else if(event->type() == QEvent::Leave) {
            _closeWg->load(QString(":/Icon/Image/frame_icon_close_hover_12x10_gray.svg"));
        }
        else if(event->type() == QEvent::MouseButtonRelease) {
            _state = NotUSING;
            emit closeItem();
            close();
        }
        else if(event->type() == QEvent::Show) {
            _state = USING;
        }
    }
    return QWidget::eventFilter(object, event);
}
