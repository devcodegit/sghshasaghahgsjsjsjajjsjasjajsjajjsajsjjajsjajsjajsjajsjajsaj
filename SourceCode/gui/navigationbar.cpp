#include "navigationbar.h"
#include "CustomControl/drop-down-widget.h"
#include "CustomControl/verticalscrollbar.h"
#include <QBoxLayout>
#include <QResizeEvent>
#include <QLabel>
#include <QDebug>
#include <QScrollArea>
#include <QScrollBar>

#define AVATAR_SIZE 100
#define AVATAR_HEADER_SIZE 200

NavigationBar *NavigationBar::Instance = 0;

NavigationBar::NavigationBar(QWidget *parent) : QFrame(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->setAlignment(Qt::AlignTop);

    QFrame *avatarHeader = new QFrame;
    avatarHeader->setFixedHeight(AVATAR_HEADER_SIZE);

    contentFrame = new QFrame;
    contentFrame->setFixedHeight(0);
    contentLayout = new QVBoxLayout(contentFrame);
    contentLayout->setSpacing(0);
    contentLayout->setMargin(0);

    scrollArea = new QScrollArea;
    scrollArea->setFocusPolicy(Qt::NoFocus);
    scrollArea->setWidget(contentFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    connect(scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollValueChanged(int)));
    scrollBar = new VerticalScrollbar(scrollArea, scrollArea->verticalScrollBar());
    scrollBar->setMargin(0);
    scrollBar->update(true);
    scrollBar->setMinHeight(30);

    QVBoxLayout *avatarLayout = new QVBoxLayout(avatarHeader);
    avatarLayout->setSpacing(8);
    avatarLayout->setMargin(0);
    avatarLayout->setAlignment(Qt::AlignCenter);

    QLabel *avatar = new QLabel;
    avatar->setFixedSize(AVATAR_SIZE, AVATAR_SIZE);
    QLabel *name = new QLabel;
    name->setText("Shop Name");

    avatarLayout->addWidget(avatar, 0, Qt::AlignCenter);
    avatarLayout->addWidget(name, 0, Qt::AlignCenter);


    mainLayout->addWidget(avatarHeader, 0, Qt::AlignTop);
    mainLayout->addWidget(scrollArea, 0, Qt::AlignTop);

    addContent("Tổng quan đơn hàng", QStringList() << "Tất cả" << "Đang xử lý" << "Sẵn sàng giao đi" << "Đang giao hàng" << "Hoàn thành");
    addContent("Quản lý giao nhận", QStringList() << "Option 1" << "Option 2");
    addContent("Quản lý nhân viên",  QStringList() << "Option 1" << "Option 2");
    addContent("Cài đặt",  QStringList() << "Option 1" << "Option 2" << "Option 3" << "Option 4");

}

void NavigationBar::addContent(const QString &title, QStringList contents)
{
    DropdownWidget *item = new DropdownWidget(contentFrame);
    connect(item, SIGNAL(dropDown()), this, SLOT(onItemDropDown()));
    item->setTitle(title);
    for(int i = 0; i < contents.length(); i++) {
        item->addContent(contents.at(i));
    }
    listItems.append(item);
    contentLayout->addWidget(item, 0, Qt::AlignLeft);
    item->adjustSize();
    contentFrame->setFixedHeight(contentFrame->height() + item->height());
}

void NavigationBar::resizeEvent(QResizeEvent *event)
{
    contentFrame->setFixedWidth(event->size().width());
    scrollArea->setFixedSize(event->size().width(), event->size().height() - AVATAR_HEADER_SIZE);
}

void NavigationBar::onItemDropDown()
{
    int h = 0;
    for(int i = 0; i < listItems.length(); i++) {
        qDebug () << "item height" << listItems.at(i)->height();
        h += listItems.at(i)->height();
    }
    contentFrame->setFixedHeight(h);
}

void NavigationBar::onScrollValueChanged(int value)
{
    qDebug () << "onScrollValueChanged();" << value;
    scrollBar->setValue(value);
}
