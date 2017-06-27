#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QObject>
#include <QMap>
#include <QList>

class DataHandler : public QObject
{
    Q_OBJECT
public:
    enum data_type {
        PLAINTEXT = 0,
        PHOTO,
        CHECKBOX,
        DROPDOWN,
        MORE

    };

    struct data_handler {
        int id;
        int row;
        int col;
        data_type type;
        QString title;
        QString thumbUrl;
        bool isChecked;
        QMap<int, QString> dropdownList; // <id, title>
        int moreId;
        data_handler(int id, int row, int col, data_type type, QString title, QString thumbUrl, bool isChecked, QMap<int, QString> dropdownList, int moreId) {
            this->id = id;
            this->row = row;
            this->col = col;
            this->type = type;
            this->title = title;
            this->thumbUrl =thumbUrl;
            this->isChecked = isChecked;
            this->dropdownList = dropdownList;
            this->moreId = moreId;
        }
    };

    explicit DataHandler(QObject *parent = 0);
    QList<QList<data_handler *> > getData();
    QList<QList<data_handler *> > getData(int page);
    void addRow(QList<data_handler*> rowContents, int index = -1);
    void removeRow(int rowIndex);
    int rowCount();
    void setMaxRowPerPage(int max);
    int pageCount();

signals:

public slots:
private:
    int _rowCount = 0;
    int _maxRowPerPage;
    QList<QList<data_handler *> > _data;
};

#endif // DATAHANDLER_H
