#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QStringList>
#include <QVariant>
#include <QMap>

class QStandardItemModel;
class QStandardItem;

class TableModel
{
    TableModel();
    static TableModel *Instance;
public:
    enum {
        TABLE_MAIN = 0,
        TABLE_EXPORT,
        TABLE_READY,
        TABLE_PROCESSING,
        TABLE_TRANSMITTING,
        TABLE_DONE
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
    void setHorizontalHeaderLabels(QStringList headerList, int modelId);

private:
    QMap<int, QStandardItemModel*> mapModel;
};

#endif // TABLEMODEL_H
