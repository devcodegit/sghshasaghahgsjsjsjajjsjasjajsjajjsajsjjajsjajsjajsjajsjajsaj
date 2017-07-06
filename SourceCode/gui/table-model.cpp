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
        QStandardItem *item = new QStandardItem;
        if(rowData.at(col) == "[]") {
            item->setData(QVariant(false), Qt::EditRole);
        }
        else {
            item->setData(QVariant(rowData.at(col)), Qt::DisplayRole);
        }
        model->setItem(row, col, item);
    }
}

void TableModel::updateModel(int row, int col, QVariant data, int modelId)
{
    QStandardItemModel *model = getModel(modelId);
    QStandardItem *item = model->item(row, col);
    if(item) {
        item->setData(data, Qt::EditRole);
    }
}

void TableModel::setHorizontalHeaderLabels(QStringList headerList, int modelId)
{
    QStandardItemModel *model = getModel(modelId);
    model->setHorizontalHeaderLabels(headerList);
}
