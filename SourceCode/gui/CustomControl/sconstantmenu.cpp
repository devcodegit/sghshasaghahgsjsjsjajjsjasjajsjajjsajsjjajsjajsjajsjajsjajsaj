#include "sconstantmenu.h"
#include <QBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QEvent>
#include <QDebug>

SConstantMenu::SConstantMenu(QWidget *parent) : QWidget(parent)
{
    leaveItemTimer.setSingleShot(true);
    leaveItemTimer.setInterval(100);
    connect(&leaveItemTimer, SIGNAL(timeout()), this, SLOT(onHidePreview()));

    leavePreviewTimer.setSingleShot(true);
    leavePreviewTimer.setInterval(2000);
    connect(&leavePreviewTimer, SIGNAL(timeout()), this, SLOT(onHidePreview()));
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
        preview_content->installEventFilter(this);
        mapItemContent.insert(item, preview_content);
    }
}

bool SConstantMenu::eventFilter(QObject *object, QEvent *event)
{
    if(mapItemContent.contains((QFrame*)object)) {
        if(event->type() == QEvent::Enter) {
            QWidget *preview = mapItemContent.value((QFrame*)object, 0);
            if(preview) {
                qDebug () << "enter_item";
                if(leaveItemTimer.isActive()) leaveItemTimer.stop();
                if(currentPreview) currentPreview->hide();
                currentPreview = preview;
                preview->show();
                preview->raise();
                preview->setFocus();
            }
        }
        else if(event->type() == QEvent::Leave) {
            QWidget *preview = mapItemContent.value((QFrame*)object, 0);
            if(preview) {
                qDebug () << "leave_item";
                leaveItemTimer.start();
            }
        }
        else if(event->type() == QEvent::Resize) {
            QWidget *preview = mapItemContent.value((QFrame*)object, 0);
            if(preview) {
                QFrame *w = (QFrame*)object;
                preview->move(w->width() - 5, 0);
            }
        }
    }
    else if(object == currentPreview) {
        if(event->type() == QEvent::Enter) {
            qDebug () << "enter_preview";
            enteredPreview = true;
            if(leavePreviewTimer.isActive()) leavePreviewTimer.stop();
        }
        else if(event->type() == QEvent::Leave) {
            qDebug () << "leave_preview";
            enteredPreview = false;
            if(leavePreviewTimer.isActive()) leavePreviewTimer.stop();
            leavePreviewTimer.start();
        }
    }
    return QWidget::eventFilter(object, event);
}

void SConstantMenu::onHidePreview()
{
    if(currentPreview && !enteredPreview) {
        if(leavePreviewTimer.isActive()) leavePreviewTimer.stop();
        currentPreview->hide();
    }
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

