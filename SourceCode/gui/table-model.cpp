#include "table-model.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>

TableModel *TableModel::Instance = 0;
TableModel::TableModel()
{

}

QStandardItemModel *TableModel::getModel(int modelId)
{
    QStandardItemModel *model = mapModel.value(modelId, 0);
    if(model) return model;
    model = new QStandardItemModel;
    mapModel.insert(modelId, model);
    return model;
}

void TableModel::pushItem(QStringList rowData, int modelId)
{
    QStandardItemModel *model = getModel(modelId);
    int row = model->rowCount();
    for(int col = 0; col < rowData.length(); col++) {
        QStandardItem *item;
        if(rowData.at(col) == "[]") {
            item = new QStandardItem;
            item->setData(QVariant(true), Qt::EditRole);
        }
        else item = new QStandardItem(rowData.at(col));
        model->setItem(row, col, item);
    }
}

void TableModel::updateModel(int row, int col, QVariant data, int modelId)
{
    QStandardItemModel *model = getModel(modelId);
    QStandardItem *item = model->takeItem(row, col);
    if(item) {
        qDebug () << "updateModel" << row << col << data;
        item->setData(data, Qt::EditRole);
        model->setItem(row, col, item);
    }
}
