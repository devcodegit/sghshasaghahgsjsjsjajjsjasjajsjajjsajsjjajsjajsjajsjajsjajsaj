#include "datahandler.h"
#include <QDebug>

#define DEFAULT_MAX_ROW_PER_PAGE 20

DataHandler::DataHandler(QObject *parent) : QObject(parent)
{
    this->_maxRowPerPage = DEFAULT_MAX_ROW_PER_PAGE;
}

QList<QList<DataHandler::data_handler *> > DataHandler::getData()
{
    return this->_data;
}

QList<QList<DataHandler::data_handler *> > DataHandler::getData(int page)
{
    QList<QList<DataHandler::data_handler *> > pageData;
    int start = (page - 1) * _maxRowPerPage;
    int length = qMin(_data.length() - start, _maxRowPerPage);
    qDebug () << "dataLENGHT = " << length;
    pageData = this->_data.mid(start, length);
    return pageData;
}

void DataHandler::addRow(QList<DataHandler::data_handler *> rowContents, int index)
{
    this->_rowCount++;
    if(index > -1) {
        this->_data.insert(index, rowContents);
        return;
    }
    this->_data.append(rowContents);
}

void DataHandler::removeRow(int rowIndex)
{
    this->_rowCount--;
    if(rowIndex < 0 || rowIndex >= this->_data.length()) return;
    this->_data.removeAt(rowIndex);
}

int DataHandler::rowCount()
{
    return this->_rowCount;
}

void DataHandler::setMaxRowPerPage(int max)
{
    this->_maxRowPerPage = max;
}

int DataHandler::pageCount()
{
    int del = this->_rowCount % this->_maxRowPerPage;
    return (this->_rowCount / this->_maxRowPerPage) + (del > 0 ? 1 : 0);
}
