#include "leftpanel.h"
#include "../style-sheet-manager.h"
#include "../uiconst.h"
#include "../signalsender.h"
#include <QSvgWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QKeyEvent>

#define MARGIN_LEFT 4
#define ITEM_WIDTH (LEFT_PANEL_WIDTH-MARGIN_LEFT)
#define ITEM_HEIGHT 100

LeftPanel::LeftPanel(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(MARGIN_LEFT,0,0,0);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    addItem(":/Icon/Image/home.svg", "Home", LeftPanelItem::ID_HOME);
    addItem(":/Icon/Image/home.svg", "Quản lý đơn hàng", LeftPanelItem::ID_MANAGEMENT);
    addItem(":/Icon/Image/home.svg", "Thiết lập", LeftPanelItem::ID_SETTING);

}

void LeftPanel::addItem(const QString &svgIcon, const QString &title, int id)
{
    LeftPanelItem *item = new LeftPanelItem;
    item->setIcon(svgIcon, QSize(20,20));
    item->setTitle(title);
    item->setId(id);
    mainLayout->addWidget(item, 0, Qt::AlignTop | Qt::AlignLeft);
}

LeftPanelItem::LeftPanelItem(QWidget *parent) : QFrame(parent)
{
    setObjectName("LeftPanelItem");
    setFixedSize(ITEM_WIDTH, ITEM_HEIGHT);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(8);
    layout->setMargin(0);
    layout->setAlignment(Qt::AlignCenter);

    title = new QLabel;
    title->setWordWrap(true);
    title->setFixedWidth(ITEM_WIDTH - 20);
    title->setAlignment(Qt::AlignCenter);
    icon = new QSvgWidget;
    layout->addWidget(icon, 0, Qt::AlignCenter);
    layout->addWidget(title, 0, Qt::AlignCenter);
    setCursor(Qt::PointingHandCursor);
}

void LeftPanelItem::setTitle(const QString &title)
{
    this->title->setText(title);
}

void LeftPanelItem::setIcon(const QString &svgIcon, QSize size)
{
    if(svgIcon.isEmpty()) {
        this->icon->hide();
        return;
    }
    this->icon->setFixedSize(size);
    this->icon->load(svgIcon);
    this->icon->show();
}

void LeftPanelItem::setId(int id)
{
    this->id = id;
}

void LeftPanelItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        switch(this->id) {
        case ID_HOME:
            emit SignalSender::instance()->homeClicked();
            break;
        case ID_MANAGEMENT:
            emit SignalSender::instance()->managementClicked();
            break;
        case ID_SETTING:
            emit SignalSender::instance()->settingClicked();
            break;
        default:
            break;
        }
    }
}

void LeftPanelItem::enterEvent(QEvent *)
{
    StyleSheetManager::changeProperty(this, "State", "Hover");
}

void LeftPanelItem::leaveEvent(QEvent *)
{
    StyleSheetManager::changeProperty(this, "State", "");
}
