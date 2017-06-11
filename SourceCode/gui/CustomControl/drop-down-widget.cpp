#include "drop-down-widget.h"
#include "svgwidget.h"
#include <QBoxLayout>
#include <QLabel>
#include <QSvgWidget>
#include <QDebug>

#define TITLE_HEIGHT 50
#define ICON_HEIGHT 7
#define ICON_WIDTH 15
#define MARGIN 8

DropdownWidget::DropdownWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(MARGIN);

    titleFrame = new QFrame;
    titleFrame->setFixedHeight(TITLE_HEIGHT);
    contentFrame = new QFrame;
    contentFrame->hide();

    QHBoxLayout *titleLayout = new QHBoxLayout(titleFrame);
    titleLayout->setSpacing(0);
    titleLayout->setMargin(0);
    title = new QLabel;
    iconDropdown = new SvgWidget;
    iconDropdown->setFixedSize(ICON_HEIGHT, ICON_WIDTH);
    iconDropdown->setCursor(Qt::PointingHandCursor);
    iconDropdown->load(QString(":/Icon/Image/arrow-down_2.svg"));
    connect(iconDropdown, SIGNAL(onClicked()), this, SLOT(onDropdown()));
    titleLayout->addWidget(title, 0, Qt::AlignLeft);
    titleLayout->addWidget(iconDropdown, 0, Qt::AlignRight);

    mainLayout->addWidget(titleFrame);
    mainLayout->addWidget(contentFrame);
}

void DropdownWidget::addContent(const QString &titleContent)
{
    if(!contentLayout) {
        contentLayout = new QVBoxLayout(contentFrame);
        contentLayout->setSpacing(0);
        contentLayout->setMargin(0);
    }
    QLabel *content = new QLabel;
    content->setWordWrap(true);
    content->setText(titleContent);
    contentLayout->addWidget(content, 0, Qt::AlignTop | Qt::AlignLeft);
    listContent.append(content);
}

void DropdownWidget::setTitle(const QString &title)
{
    this->title->setText(title);
}

bool DropdownWidget::eventFilter(QObject *object, QEvent *event)
{
    return QWidget::eventFilter(object, event);
}

void DropdownWidget::resizeEvent(QResizeEvent *event)
{
    int h = 0;
    for(int i = 0; i < listContent.length(); i++) {
        QLabel *contentItem = listContent.at(i);
        if(!contentItem) continue;
        contentItem->setFixedWidth(event->size().width());
        contentItem->adjustSize();
        h += contentItem->height();
    }
    contentFrame->setFixedHeight(h);
}

void DropdownWidget::onDropdown()
{
    isDropdownShow = !isDropdownShow;
    int h = 0;
    if(isDropdownShow) {
        contentFrame->show();
        iconDropdown->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
        iconDropdown->load(QString(":/Icon/Image/arrow-down.svg"));
        h = titleFrame->height() + contentFrame->height() + 2 * MARGIN;
    }
    else {
        contentFrame->hide();
        iconDropdown->setFixedSize(ICON_HEIGHT, ICON_WIDTH);
        iconDropdown->load(QString(":/Icon/Image/arrow-down_2.svg"));
        h = titleFrame->height() + 2 * MARGIN;
    }
    this->setFixedHeight(h);
}
