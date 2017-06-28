#ifndef TINYTABLEWIDGET_H
#define TINYTABLEWIDGET_H

#include <QWidget>
#include <QStringList>
#include <QMap>
#include <QFrame>
#include <QList>
#include "datahandler.h"

class QLabel;
class QHBoxLayout;
class QGridLayout;
class QCheckBox;
class QScrollArea;
class VerticalScrollbar;
class HorizontalScrollBar;
class TableCell;

class TinyTableWidget : public QFrame
{
    Q_OBJECT
public:
    explicit TinyTableWidget(QWidget *parent = 0);
    void setHeader(QStringList headers);
    void setData(QList<QList<DataHandler::data_handler *> > data);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

signals:

public slots:

private slots:
    void onDataChanged();
    void onUpdateSize(int row, int col, QSize size);
    void onVerScrollValueChanged(int value);
    void onHorScrollValueChanged(int value);

private:
    QList<TableCell*> listHeader;
    QMap<int, QMap<int, TableCell*> > mapCells;
    QFrame *headerFrame = 0;
    QGridLayout *mainLayout = 0;
    int startResize = -1;
    int inLimitZone = -1;
    int currentX = -1;
    int rowCount = 0;

    QWidget *scroll;
    QScrollArea *scrollArea;
    VerticalScrollbar *verScrollBar;
    HorizontalScrollBar *horScrollBar;
    QList<TableCell *> listCells;

private:
    void initUI();
    void resizeColumn(int index, int width);
    void resizeRow(int index, int height);
    void cacheCell(TableCell *cell);
    void cacheOldCells();
    TableCell* getCell();
};

#endif // TINYTABLEWIDGET_H
