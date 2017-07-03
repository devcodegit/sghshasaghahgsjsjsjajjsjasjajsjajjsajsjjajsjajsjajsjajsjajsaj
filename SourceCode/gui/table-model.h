#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QStringList>
#include <QVariant>

class QStandardItemModel;

class TableModel
{
    TableModel();
    static TableModel *Instance;
public:
    static TableModel *instance() {
        if(!Instance) {
            Instance = new TableModel;
        }
        return Instance;
    }

    QStandardItemModel *getModel();
    void pushItem(QStringList rowData);
    void updateModel(int row, int col, QVariant data);

private:
    QStandardItemModel *model = 0;
};

#endif // TABLEMODEL_H
