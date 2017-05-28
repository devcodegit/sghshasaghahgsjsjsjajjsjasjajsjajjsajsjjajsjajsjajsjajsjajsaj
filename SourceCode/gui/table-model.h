#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QStringList>

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

private:
    QStandardItemModel *model = 0;
};

#endif // TABLEMODEL_H
