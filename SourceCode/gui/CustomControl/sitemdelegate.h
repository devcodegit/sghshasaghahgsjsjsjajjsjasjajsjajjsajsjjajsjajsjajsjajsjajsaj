#ifndef SITEMDELEGATE_H
#define SITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QModelIndex>

class QPushButton;

class SItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SItemDelegate(QWidget *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

signals:
    void paintItem(const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // SITEMDELEGATE_H
