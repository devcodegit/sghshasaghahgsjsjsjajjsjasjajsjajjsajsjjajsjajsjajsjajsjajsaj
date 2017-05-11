#include "sconstantmenu.h"
#include <QBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QEvent>
#include <QDebug>

SConstantMenu::SConstantMenu(QWidget *parent) : QWidget(parent)
{

}

void SConstantMenu::addItem(const QString &title, QWidget *preview_content)
{
    if(!itemLayout) {
        itemLayout = new QVBoxLayout(this);
        itemLayout->setSpacing(0);
        itemLayout->setMargin(0);
        itemLayout->setAlignment(Qt::AlignTop);
    }
    QFrame *item = createItem(title, preview_content ? true : false);
    item->installEventFilter(this);
    itemLayout->addWidget(item);
    if(preview_content) {
        if(this->parentWidget()) preview_content->setParent(this->parentWidget()->parentWidget());
        else preview_content->setParent(this->parentWidget());
        preview_content->hide();
        mapItemContent.insert(item, preview_content);
    }
}

bool SConstantMenu::eventFilter(QObject *object, QEvent *event)
{
    if(mapItemContent.contains((QFrame*)object)) {
        if(event->type() == QEvent::Enter) {
            QWidget *preview = mapItemContent.value((QFrame*)object, 0);
            if(preview) {
                preview->show();
                preview->raise();
            }
        }
        else if(event->type() == QEvent::Leave) {
            QWidget *preview = mapItemContent.value((QFrame*)object, 0);
            if(preview) {
                preview->hide();
            }
        }
        else if(event->type() == QEvent::Resize) {
            QWidget *preview = mapItemContent.value((QFrame*)object, 0);
            if(preview) {
                QFrame *w = (QFrame*)object;
                preview->move(w->width(), 0);
            }
        }
    }
    return QWidget::eventFilter(object, event);
}

QFrame *SConstantMenu::createItem(const QString &title, bool hasIcon)
{
    QFrame *item = new QFrame(this);
    item->setCursor(Qt::PointingHandCursor);
    QHBoxLayout *layout = new QHBoxLayout(item);
    layout->setSpacing(0);
    layout->setMargin(4);
    QLabel *titleLbl = new QLabel(title, item);
    layout->addWidget(titleLbl, 1, Qt::AlignLeft);
    if(hasIcon){
        QLabel *iconLbl = new QLabel(item);
        iconLbl->setPixmap(QPixmap(":/Icon/Image/arrow-point-to-right.svg").scaled(15, 15, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        iconLbl->setFixedSize(15,15);
        layout->addWidget(iconLbl, 0, Qt::AlignRight);
    }
    return item;
}

