#include "sdialog.h"
#include "svgwidget.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QEvent>
#include <QLabel>
#include <QDebug>

#define TITLE_BAR_HEIGHT 30

SDialog::SDialog(QWidget *parent) : QWidget(parent)
{
    setParent(parent);
    background = new QFrame(this);
    background->setObjectName("BackgroundLockWindow");
    background->installEventFilter(this);
    background->move(0,0);
    QHBoxLayout *mainLayout = new QHBoxLayout(background);
    mainLayout->setAlignment(Qt::AlignCenter);

    content = new QFrame;
    content->setObjectName("ContentDialog");
    titleBar = new QLabel(content);
    titleBar->installEventFilter(this);
    titleBar->setContentsMargins(8,0,8,0);
    titleBar->setObjectName("TitleBarDialog");
    titleBar->setFixedHeight(TITLE_BAR_HEIGHT);
    titleBar->show();
    closeButton = new SvgWidget(titleBar, ":/Icon/Image/frame_icon_close_hover_12x10_gray.svg",  ":/Icon/Image/frame_icon_close_12x10_white_hover.svg");
    closeButton->setFixedSize(12,10);
    closeButton->setToolTip("Đóng");
    closeButton->setCursor(Qt::PointingHandCursor);
    closeButton->show();
    connect(closeButton, SIGNAL(onClicked()), this, SLOT(close()));
    mainLayout->addWidget(content,1);

}

void SDialog::setParent(QWidget *parent)
{
    this->parent = parent;
    if(parent) {
        parent->installEventFilter(this);
        setFixedSize(parent->size());
    }
    QWidget::setParent(parent);
}

void SDialog::setContent(QWidget *content)
{
    content->setParent(this->content);
    content->move(0, TITLE_BAR_HEIGHT);
    content->show();
    this->content->setFixedSize(content->size() + QSize(0,TITLE_BAR_HEIGHT));
    this->titleBar->setFixedWidth(content->width());
}

void SDialog::setWindowTitle(const QString &title)
{
    this->titleBar->setText(title);
}

void SDialog::updateContentSize(QSize size)
{
    this->content->setFixedSize(size + QSize(0, TITLE_BAR_HEIGHT));
}

bool SDialog::eventFilter(QObject *object, QEvent *event)
{
    if(object == parent) {
        if(event->type() == QEvent::Resize) {
            this->setFixedSize(parent->size());
        }
    }
    else if(object == titleBar) {
        if(event->type() == QEvent::Resize) {
            closeButton->move(titleBar->width() - closeButton->width() - 8, (titleBar->height() - closeButton->height())/2);
        }
    }
    return QWidget::eventFilter(object, event);
}

void SDialog::resizeEvent(QResizeEvent *event)
{
    background->setFixedSize(event->size());
}
