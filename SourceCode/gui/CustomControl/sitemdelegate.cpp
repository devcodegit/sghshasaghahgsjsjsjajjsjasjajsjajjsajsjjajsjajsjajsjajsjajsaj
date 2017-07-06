#include "sitemdelegate.h"
#include "testingcellui.h"
#include "cache.h"
#include "../../uiconst.h"
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
    QColor color;
    if(index.row() %2 == 0) {
        color = QColor("#e2e6ea");
    }
    else {
        color = QColor(Qt::white);
    }
    if( option.state & QStyle::State_Selected ) {
        painter->fillRect( option.rect, option.palette.highlight());
    }
    painter->fillRect(option.rect, color);
    if(index.column() == CHECKBOX_COL && !noCheckCol) {
        // Draw our checkbox indicator
        bool value = index.data(Qt::EditRole).toBool();
        QStyleOptionButton checkbox_indicator;

        // Set our button state to enabled
        checkbox_indicator.state |= QStyle::State_Enabled;
        checkbox_indicator.state |= (value) ? QStyle::State_On : QStyle::State_Off;

        // Get our deimensions
        checkbox_indicator.rect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &checkbox_indicator, NULL );

        // Position our indicator
        const int x = option.rect.center().x() - checkbox_indicator.rect.width() / 2;
        const int y = option.rect.center().y() - checkbox_indicator.rect.height() / 2;

        checkbox_indicator.rect.moveTo( x, y );

        if (option.state & QStyle::State_Selected) {
            painter->fillRect(option.rect, option.palette.highlight());
        }

        return QApplication::style()->drawControl( QStyle::CE_CheckBox, &checkbox_indicator, painter );
    }
    QStyledItemDelegate::paint(painter, option, index);
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

void SItemDelegate::setShowCheckCol(bool isShowChecked)
{
    this->noCheckCol = !isShowChecked;
}

