#ifndef STABLEVIEW_H
#define STABLEVIEW_H

#include <QTableView>
#include <QStyledItemDelegate>
#include <QModelIndex>

class SItemDelegate;

class STableView : public QTableView
{
    Q_OBJECT
public:
    explicit STableView(QWidget *parent = 0);

signals:

public slots:
private slots:
    void onPaintItem(const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    SItemDelegate* delegate;
};

#endif // STABLEVIEW_H
