#include "table-model.h"
#include <QStandardItemModel>
#include <QStandardItem>

TableModel *TableModel::Instance = 0;
TableModel::TableModel()
{

}

QStandardItemModel *TableModel::getModel()
{
    if(!model)
        model = new QStandardItemModel;
    return model;
}

void TableModel::pushItem(QStringList rowData)
{
    getModel();
    int row = model->rowCount();
    for(int col = 0; col < rowData.length(); col++) {
        QStandardItem *item = new QStandardItem(rowData.at(col));
        model->setItem(row, col, item);
    }
}
