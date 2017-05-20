#include "stableview.h"
#include "sitemdelegate.h"
#include "cache.h"
#include <QDebug>
#include <QPushButton>
#include <QScrollBar>
#include <QHeaderView>

STableView::STableView(QWidget *parent) : QTableView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    delegate = new SItemDelegate;
    connect(delegate, SIGNAL(paintItem(QStyleOptionViewItem,QModelIndex)), this, SLOT(onPaintItem(QStyleOptionViewItem,QModelIndex)));
    setItemDelegate(delegate);
    connect(this, SIGNAL(pressed(QModelIndex)), this, SLOT(onPressed(QModelIndex)));
    connect(this->verticalHeader(), SIGNAL(sectionResized(int,int,int)), this, SLOT(rowResized(int,int,int)));
    connect(this->horizontalHeader(), SIGNAL(sectionResized(int,int,int)), this, SLOT(columnResized(int,int,int)));
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));

}

void STableView::rowResized(int row, int oldHeight, int newHeight)
{
    qDebug () << "rowResize" << row << oldHeight <<newHeight;
}

void STableView::columnResized(int column, int oldWidth, int newWidth)
{
    QModelIndex index = this->model()->index(1, column);
    qDebug () << "columnResize" << column << oldWidth << newWidth;
}

void STableView::onPaintItem(const QStyleOptionViewItem &option, const QModelIndex &index)
{
//    QPushButton *button = Cache::instance()->getWidget(index.row());
//    qDebug () << "paintItem" << index.data() << option.rect << index.row();
//    button->setParent(this->viewport());
//    button->setText(index.data().toString());
//    button->show();
//    button->setGeometry(option.rect);
    mapIndexOption.insert(index, option);
//    qDebug () << "paint____" << index << option.rect;

}

void STableView::onPressed(const QModelIndex &index)
{
    qDebug () << "Pressed" << index.data() << index.column() << index.row();
    for(QMap<QModelIndex, QStyleOptionViewItem>::iterator it = mapIndexOption.begin(); it != mapIndexOption.end(); it++) {
        qDebug () << "here" << it.value() << it.key();
    }
    emit itemClicked();
//    int height = 0;
//    int _index = currentValue;
//    while(true) {
//        QModelIndex index = this->model()->index(_index, 3);
//        if(!index.isValid()) break;
//        QPushButton *button = Cache::instance()->getWidget(index.row());
//        button->setParent(this->viewport());
//        button->setText(index.data().toString());
//        button->show();
//        button->setGeometry(mapIndexOption.value(index).rect);
//        height += button->height();
//        qDebug () << _index << button->geometry() << height << index.data() << mapIndexOption.value(index).rect;
//        if(height >= this->viewport()->size().height()) break;
//        _index++;
//    }

}

void STableView::onScrollBarValueChanged(int value)
{
    qDebug () << "onScrollBarValueChanged();" << value;
    currentValue = value;
}

