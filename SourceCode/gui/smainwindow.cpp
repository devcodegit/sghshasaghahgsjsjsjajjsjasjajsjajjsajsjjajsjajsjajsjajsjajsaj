#include "smainwindow.h"
#include "SourceCode/uiconst.h"

#include "CustomControl/sconstantmenu.h"
#include "CustomControl/stabwidget.h"
#include "../uimodel.h"
#include "page-search.h"
#include "../lazada/lazada_handler.h"
#include "leftpanel.h"
#include "../signalsender.h"
#include "suserinfo.h"
#include "CustomControl/drop-down-widget.h"
#include "navigationbar.h"
#include "CustomControl/table/tinytablewidget.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QStackedWidget>
#include <QEvent>

#define AVATAR_SIZE 30

using namespace Lazada::Controls;

SMainWindow::SMainWindow(QWidget *parent) : SWidget(parent)
{
    setObjectName("MainBackground");
    setMinimumSize(800,600);
    createNavigation();
    createHeader();
    createMidle();

    UIModel::instance()->setMainWindow(this);
    onManagementClicked();

    TinyTableWidget *table = new TinyTableWidget;
    table->show();


    DataHandler *dataHandler = new DataHandler;
    int count = 0;
    for(int j = 0; j < 30; j++) {
        QList<DataHandler::data_handler *> row;
        for(int i = 0; i < 5; i++) {
            DataHandler::data_type type = (DataHandler::data_type)i;

            bool isChecked =(i % 2 == 0);
            int id = count;
            row.append(new DataHandler::data_handler(id, count, i, type, QString("Test %1 %2").arg(count).arg(i), "", isChecked, QMap<int,QString>(), id));
        }
        count++;
        dataHandler->addRow(row);
    }
    table->setData(dataHandler);

}

void SMainWindow::onManagementClicked()
{
    if(!pageSearch) {
        pageSearch = new PageSearch(contentArea);
    }
    pageSearch->show();
}

void SMainWindow::resizeEvent(QResizeEvent *ev)
{
    Q_UNUSED(ev);
    updateSize();
}

bool SMainWindow::eventFilter(QObject *object, QEvent *event)
{
    if(object == avatar || object == info) {
        if(event->type() == QEvent::MouseButtonRelease) {
            SUserInfo::instance()->setParent(this);
            SUserInfo::instance()->show();
        }
    }
    return SWidget::eventFilter(object, event);
}

void SMainWindow::createHeader()
{
    if (!headerArea)
    {
        headerArea = new QFrame(this);
        headerArea->setObjectName("HeaderMainWindow");
        headerArea->setFixedHeight(SIZE_HEIGHT_HEADER);
        headerArea->move(LEFT_PANEL_WIDTH, 0);


        QHBoxLayout *layout = new QHBoxLayout(headerArea);
        layout->setSpacing(8);
        layout->setMargin(0);
        layout->setAlignment(Qt::AlignRight);

        avatar = new QLabel;
        avatar->setCursor(Qt::PointingHandCursor);
        avatar->setPixmap(QPixmap(":/Icon/Image/avatar_user_default.png").scaled(AVATAR_SIZE, AVATAR_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        avatar->installEventFilter(this);
        info = new QLabel;
        info->installEventFilter(this);
        info->setCursor(Qt::PointingHandCursor);
        info->setText("Xin chào, Nguyễn Văn A");
        QPushButton *logOutButton = new QPushButton("Thoát");
        logOutButton->setIcon(QIcon(":/Icon/Image/exit.svg"));

        layout->addWidget(avatar, 0, Qt::AlignRight);
        layout->addWidget(info, 0, Qt::AlignRight);
        layout->addWidget(logOutButton, 0, Qt::AlignRight);
    }

}

void SMainWindow::createMidle()
{
    if (!contentArea)
    {
        contentArea = new QFrame(this);
        contentArea->move(LEFT_PANEL_WIDTH, SIZE_HEIGHT_HEADER);
        contentArea->show();
    }
}

void SMainWindow::createNavigation()
{
    if (!navigationArea)
    {
        navigationArea = new QFrame(this);
        navigationArea->move(0,0);
        navigationArea->show();
        navigationArea->setObjectName("MidleStyleOption");
        navigationArea->setFixedWidth(LEFT_PANEL_WIDTH);

        NavigationBar::instance()->setParent(navigationArea);
        NavigationBar::instance()->move(0,1);
        NavigationBar::instance()->show();
    }

}

void SMainWindow::updateSize()
{
    if (navigationArea)
    {
        navigationArea->setFixedHeight(this->height());
        NavigationBar::instance()->setFixedSize(navigationArea->size());
    }

    if (contentArea)
    {
        contentArea->setFixedSize(this->width() - LEFT_PANEL_WIDTH, this->height());
    }

    if(headerArea) {
        headerArea->setFixedWidth(this->width() - LEFT_PANEL_WIDTH);
    }

    if(pageSearch) {
        if(contentArea) pageSearch->setFixedSize(contentArea->size());
        if(pageSearch) pageSearch->setFixedSize(pageSearch->size());
    }
}
