#include "toolbutton.h"
#include "svgwidget.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QEvent>
#include <QDebug>

#define DEFAULT_BUTTON_HEIGHT 30

ToolButton::ToolButton(QWidget *parent) : QFrame(parent)
{
    setMinimumHeight(DEFAULT_BUTTON_HEIGHT);
    setObjectName("ToolButton");
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(8);


    titleFrame = new QFrame;
    titleFrame->installEventFilter(this);
    titleFrame->setCursor(Qt::PointingHandCursor);
    QHBoxLayout *titleLayout = new QHBoxLayout(titleFrame);
    titleLayout->setMargin(0);

    title = new QLabel;
    title->setAttribute(Qt::WA_TransparentForMouseEvents);
    titleLayout->addWidget(title, 1, Qt::AlignCenter);
    arrowFrame = new QFrame;
    arrowFrame->installEventFilter(this);
    arrowFrame->setCursor(Qt::PointingHandCursor);
    arrowFrame->setFixedSize(DEFAULT_BUTTON_HEIGHT, DEFAULT_BUTTON_HEIGHT);
    arrowIcon = new SvgWidget(arrowFrame, ":/Icon/Image/arrow-down.svg");
    arrowIcon->setAttribute(Qt::WA_TransparentForMouseEvents);
    arrowIcon->setFixedSize(15, 10);
    arrowIcon->move((DEFAULT_BUTTON_HEIGHT - 15)/2, (DEFAULT_BUTTON_HEIGHT - 10)/2);
    arrowIcon->show();


    mainLayout->addWidget(titleFrame, 1);
    mainLayout->addWidget(arrowFrame, 0, Qt::AlignRight);
}

void ToolButton::setMenu(QMenu *menu)
{
    this->menu = menu;
}

void ToolButton::setDefaultAction(QAction *action)
{
    title->setText(action->text());
    this->defaultAction = action;
}

bool ToolButton::eventFilter(QObject *object, QEvent *event)
{
    if(object == arrowFrame) {
        if(event->type() == QEvent::Enter) {
            arrowIcon->setImageNormal(":/Icon/Image/arrow-down-hover.svg");
        }
        else if(event->type() == QEvent::Leave) {
            arrowIcon->setImageNormal(":/Icon/Image/arrow-down.svg");
        }
        else if(event->type() == QEvent::MouseButtonRelease) {
            onShowMenu();
        }
    }
    else if(object == titleFrame) {
        if(event->type() == QEvent::MouseButtonRelease) {
            onTriggerDefaultAction();
        }
    }
    return QFrame::eventFilter(object, event);
}

void ToolButton::onShowMenu()
{
    if(menu) {
        menu->move(this->mapToGlobal(QPoint(0,0)) + QPoint(0, this->height()));
        menu->exec();
    }
}

void ToolButton::onTriggerDefaultAction()
{
    emit defaultAction->triggered();
}
