#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QStringList>
#include <QVariant>
#include <QMap>

class QStandardItemModel;

class TableModel
{
    TableModel();
    static TableModel *Instance;
public:
    enum {
        TABLE_MAIN = 0,
        TABLE_EXPORT = 1
    };
    static TableModel *instance() {
        if(!Instance) {
            Instance = new TableModel;
        }
        return Instance;
    }

    QStandardItemModel *getModel(int modelId);
    void pushItem(QStringList rowData, int modelId);
    void updateModel(int row, int col, QVariant data, int modelId);

private:
    QMap<int, QStandardItemModel*> mapModel;
};

#endif // TABLEMODEL_H
