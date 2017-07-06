#include "drop-down-widget.h"
#include "svgwidget.h"
#include "../../signalsender.h"
#include <QBoxLayout>
#include <QLabel>
#include <QSvgWidget>
#include <QDebug>

#define TITLE_HEIGHT 50
#define ICON_HEIGHT 7
#define ICON_WIDTH 15
#define MARGIN 8
#define CONTENT_SPACING 4

DropdownWidget::DropdownWidget(QWidget *parent) : QFrame(parent)
{
    setObjectName("DropDownItem");
    this->parent = parent;
    if(parent) parent->installEventFilter(this);
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
    title->setObjectName("LeftPanelAction");
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

void DropdownWidget::addContent(ContentAction *content)
{
    if(!contentLayout) {
        contentLayout = new QVBoxLayout(contentFrame);
        contentLayout->setSpacing(CONTENT_SPACING);
        contentLayout->setMargin(0);
    }
    QLabel *contentLbl = new QLabel;
    contentLbl->setObjectName("LeftPanelSubAction");
    contentLbl->setTextFormat(Qt::RichText);
    contentLbl->setWordWrap(true);
    contentLbl->setText(QString("<style>a:link{color:#2398CA;text-decoration:none;}</style><a href=\"%1\">%2</a>").arg(content->link, content->title));
    connect(contentLbl, SIGNAL(linkActivated(QString)), this, SLOT(onLinkActivated(QString)));
    contentLayout->addWidget(contentLbl, 0, Qt::AlignTop | Qt::AlignLeft);
    listContent.append(contentLbl);
}

void DropdownWidget::setTitle(const QString &title)
{
    this->title->setText(title);
}

void DropdownWidget::setParent(QWidget *parent)
{
    this->parent = parent;
    if(parent) parent->installEventFilter(this);
    QWidget::setParent(parent);
}

bool DropdownWidget::eventFilter(QObject *object, QEvent *event)
{
    if(object == this->parent) {
        if(event->type() == QEvent::Resize) {
            this->setFixedWidth(parent->width());
        }
    }
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
        h += contentItem->height() + CONTENT_SPACING ;
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
    emit dropDown();
}

void DropdownWidget::onLinkActivated(QString link)
{
    emit SignalSender::instance()->linkTriggered(link);
}
