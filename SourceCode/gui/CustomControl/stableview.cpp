#include "stableview.h"
#include "sitemdelegate.h"
#include "cache.h"
#include <QDebug>
#include <QPushButton>

STableView::STableView(QWidget *parent) : QTableView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);

//    delegate = new SItemDelegate;
//    connect(delegate, SIGNAL(paintItem(QStyleOptionViewItem,QModelIndex)), this, SLOT(onPaintItem(QStyleOptionViewItem,QModelIndex)));
//    setItemDelegate(delegate);

}

void STableView::onPaintItem(const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QPushButton *button = Cache::instance()->getWidget(index.row());
    qDebug () << "paintItem" << index.data() << option.rect << index.row();
    button->setParent(this->viewport());
    button->setText(index.data().toString());
    button->show();
    button->setGeometry(option.rect);
}
