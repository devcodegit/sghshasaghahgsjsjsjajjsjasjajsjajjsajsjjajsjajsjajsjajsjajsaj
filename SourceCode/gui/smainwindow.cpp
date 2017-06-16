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
    _pvLayout = new QVBoxLayout(this);
    _pvLayout->setSpacing(0);
    _pvLayout->setMargin(0);
    _pvLayout->setAlignment(Qt::AlignTop);
    createHeader();
    createMidle();

    UIModel::instance()->setMainWindow(this);
    connect(SignalSender::instance(), &SignalSender::homeClicked, this, &SMainWindow::onHomeClicked);
    connect(SignalSender::instance(), &SignalSender::managementClicked, this, &SMainWindow::onManagementClicked);
    connect(SignalSender::instance(), &SignalSender::settingClicked, this, &SMainWindow::onSettingClicked);
    onManagementClicked();
}

void SMainWindow::onHomeClicked()
{
    qDebug () << "onHomeClicked";
    if(!homePage) {
        homePage = new QFrame(_pMidleResult);
        homePage->setStyleSheet("border: 2px dashed blue; background-color: white;");
        homePage->move(0,0);
        QLabel *label = new QLabel(homePage);
        label->setStyleSheet("color: #111111; font: 16px;");
        label->move(100, 100);
        label->setText("HomePage");
    }
    homePage->setFixedSize(_pMidleResult->size());
    homePage->show();
    homePage->raise();
    if(managementPage) managementPage->hide();
    if(settingPage) settingPage->hide();
}

void SMainWindow::onManagementClicked()
{
    qDebug () << "onManagementClicked";
    if(!managementPage) {
        managementPage = new STabWidget(_pMidleResult);
        QFrame *content1 = new QFrame;
        content1->setStyleSheet("border: 2px solid blue; background-color: yellow;");
        content1->setFixedSize(managementPage->size());
        pageSearch = new PageSearch;
        managementPage->addItem("Content 1", content1);
        managementPage->addItem("Content 2", pageSearch);
    }
    managementPage->setFixedSize(_pMidleResult->size());
    pageSearch->setFixedSize(managementPage->size());
    managementPage->show();
    managementPage->raise();
    if(homePage) homePage->hide();
    if(settingPage) settingPage->hide();
}

void SMainWindow::onSettingClicked()
{
    qDebug () << "onSettingClicked";
    if(!settingPage) {
        settingPage = new QFrame(_pMidleResult);
        settingPage->setStyleSheet("border: 2px dashed red; background-color: white;");
        settingPage->move(0,0);
        QLabel *label = new QLabel(settingPage);
        label->setStyleSheet("color: #111111; font: 16px;");
        label->move(100, 100);
        label->setText("SettingPage");
    }
    settingPage->setFixedSize(_pMidleResult->size());
    settingPage->show();
    settingPage->raise();
    if(homePage) homePage->hide();
    if(managementPage) managementPage->hide();
}

void SMainWindow::resizeEvent(QResizeEvent *ev)
{
    Q_UNUSED(ev);
    updateSize();
    if(_pMidleOption) NavigationBar::instance()->setFixedSize(_pMidleOption->size());
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
    if (!_pHeader)
    {
        _pHeader = new QFrame();
        _pHeader->setObjectName("HeaderMainWindow");
        _pHeader->setFixedHeight(SIZE_HEIGHT_HEADER);
        _pvLayout->addWidget(_pHeader, 1);


        QHBoxLayout *layout = new QHBoxLayout(_pHeader);
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
        QLabel *logo = new QLabel(_pHeader);
        logo->setFixedSize(113,30);
        logo->setPixmap(QPixmap(":/Icon/Image/logo.png").scaled(113, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        logo->move(10,10);
        logo->show();
        logo->raise();
    }

}

void SMainWindow::createMidle()
{
    if (!_pMidle)
    {
        _pMidle = new QFrame();
        _pMidle->setObjectName("MidleMainWindow");
        _pvLayout->addWidget(_pMidle, 1);
    }

    if (!_pMidleOption)
    {
        _pMidleOption = new QFrame(_pMidle);
        _pMidleOption->move(0,0);
        _pMidleOption->setObjectName("MidleStyleOption");
        _pMidleOption->setFixedWidth(LEFT_PANEL_WIDTH+1);
        _pMidleOption->setFixedHeight(_pMidle->height());

//        menu = new SConstantMenu(_pMidleOption);
//        menu->setFixedWidth(SIZE_WIDTH_OPTION);

//        QWidget *w = new QWidget;
//        w->setFixedSize(100,100);
//        w->setStyleSheet("border: 1px solid red; background-color: yellow;");

//        QWidget *w2 = new QWidget;
//        w2->setFixedSize(100,100);
//        w2->setStyleSheet("border: 1px solid blue;");

//        menu->addItem("Tittle 1", w);
//        menu->addItem("Tittle 2", w2);
//        menu->move(0,0);
//        menu->show();
//        LeftPanel *lelftPanel = new LeftPanel(_pMidleOption);
//        lelftPanel->setFixedWidth(LEFT_PANEL_WIDTH);
//        lelftPanel->move(0,1);
//        lelftPanel->show();

        NavigationBar::instance()->setParent(_pMidleOption);
        NavigationBar::instance()->move(0,1);
        NavigationBar::instance()->show();
    }

    if (!_pMidleResult)
    {
        _pMidleResult = new QFrame(_pMidle);
        _pMidleResult->move(_pMidleOption->width(), 0);
        _pMidleResult->setFixedSize(_pMidle->width() - _pMidleOption->width(), _pMidle->height());
    }
}

void SMainWindow::updateSize()
{
    if (_pMidleOption)
    {
        _pMidleOption->setFixedHeight(_pMidle->height());
    }

    if (_pMidleResult)
    {
        _pMidleResult->setFixedSize(_pMidle->width() - _pMidleOption->width(), _pMidle->height());
    }

    if(managementPage) {
        if(_pMidleResult) managementPage->setFixedSize(_pMidleResult->size());
        if(pageSearch) pageSearch->setFixedSize(managementPage->size());
    }
    if(homePage) {
        if(_pMidleResult) {
            homePage->setFixedSize(_pMidleResult->size());
        }
    }
    if(settingPage) {
        if(_pMidleResult) {
            settingPage->setFixedSize(_pMidleResult->size());
        }
    }
}
