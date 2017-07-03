#include "stableview.h"
#include "sitemdelegate.h"
#include "cache.h"
#include "../../uiconst.h"
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
    mapIndexOption.insert(index, option);

}

void STableView::onPressed(const QModelIndex &index)
{
    qDebug () << "onPressed" << index.column() << index.data();
    if(index.column() == CHECKBOX_COL) {
        bool isChecked = index.data().toBool();
        emit updateCheckbox(index.row(), index.column(), !isChecked);
        return;
    }
    emit itemClicked(index.row(), index.column());

}

void STableView::onScrollBarValueChanged(int value)
{
    qDebug () << "onScrollBarValueChanged();" << value;
    currentValue = value;
}

