#ifndef STABLEVIEW_H
#define STABLEVIEW_H

#include <QTableView>
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QMap>
#include <QStyleOptionViewItem>

class SItemDelegate;

class STableView : public QTableView
{
    Q_OBJECT
public:
    explicit STableView(QWidget *parent = 0);
    void setShowCheckCol(bool isShowChecked);

protected slots:
    void rowResized(int row,  int oldHeight, int newHeight);
    void columnResized(int column, int oldWidth, int newWidth);

signals:
    void itemClicked(int row, int col);
    void updateCheckbox(int row, int col, bool state);

public slots:
private slots:
    void onPaintItem(const QStyleOptionViewItem &option, const QModelIndex &index);
    void onPressed(const QModelIndex &index);
    void onScrollBarValueChanged(int value);

private:
    SItemDelegate* delegate;
    QMap<QModelIndex, QStyleOptionViewItem> mapIndexOption;
    int currentValue = 0;
};

#endif // STABLEVIEW_H
