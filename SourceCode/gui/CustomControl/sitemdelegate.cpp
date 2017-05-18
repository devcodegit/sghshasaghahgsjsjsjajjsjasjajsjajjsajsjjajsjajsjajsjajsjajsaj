#include "sitemdelegate.h"
#include "testingcellui.h"
#include "cache.h"
#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QPushButton>

SItemDelegate::SItemDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{
}

void SItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 3) {
        emit paintItem(option, index);
    }
//    else {
        QStyledItemDelegate::paint(painter, option, index);
//    }
}

QSize SItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *SItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug () << "createEditor#0" << index.row() << index.column() << parent;
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void SItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug () << "setEditorData" << index.data().toString() << editor;
    QStyledItemDelegate::setEditorData(editor, index);
}

void SItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    qDebug () << "setModelData" << index.data().toString();
    //    QStyledItemDelegate::setModelData(editor, model, index);
}

