#include "tinytablewidget.h"
#include "../verticalscrollbar.h"
#include "../horizontalscrollbar.h"
#include "../../../style-sheet-manager.h"
#include "../../../signalsender.h"
#include "tablecell.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <QEvent>
#include <QApplication>
#include <QCheckBox>
#include <QPixmap>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>

#define HEADER_HEIGHT 50
#define ROW_HEIGHT 50
#define ROW_WIDTH 150
#define LIMIT_RESIZE 5

TinyTableWidget::TinyTableWidget(QWidget *parent) : QFrame(parent)
{
    initUI();
}

void TinyTableWidget::setHeader(QStringList headers)
{
    listHeader.clear();
    for(int i = 0; i < headers.length(); i++) {
        TableCell *headerItem = getCell();
        headerItem->setCursor(Qt::PointingHandCursor);
        headerItem->setMouseTracking(true);
        headerItem->installEventFilter(this);
        headerItem->setFixedHeight(ROW_HEIGHT);
        headerItem->setIndex(0, i);
        headerItem->setText(headers.at(i), true);
        mainLayout->addWidget(headerItem, 0, i, 1, 1);
        listHeader.append(headerItem);
    }
}

void TinyTableWidget::setData(QList<QList<DataHandler::data_handler *> > data)
{
    rowCount = data.length();
    cacheOldCells();
    this->scroll->setFixedHeight(0);
    for(int row = 0; row < data.length(); row++) {
        QMap<int, TableCell*> mapCols;
        int height = 0;
        for(int col = 0; col < data.at(row).length(); col++) {
            TableCell* cell =  getCell();
            cell->setData(data.at(row).at(col));
            cell->setCursor(Qt::PointingHandCursor);
            cell->installEventFilter(this);
            cell->setFixedHeight(100);
            cell->setIndex(row+1, col);
            connect(cell, SIGNAL(updateSize(int,int,QSize)), this, SLOT(onUpdateSize(int,int,QSize)));
            mainLayout->addWidget(cell, row+1, col, 1, 1);
            cell->show();
            mapCols.insert(col, cell);
            height = qMax(height, cell->height());
        }
        mapCells.insert(row+1, mapCols);
        this->scroll->setFixedHeight(height + this->scroll->height());
    }
}

bool TinyTableWidget::eventFilter(QObject *object, QEvent *event)
{
    if(listHeader.contains((TableCell*)object)) {
        if(event->type() == QEvent::MouseButtonRelease) {
            startResize = -1;
        }
        else if(event->type() == QEvent::MouseButtonPress) {
            startResize = inLimitZone;
            TableCell *currentHeader = (TableCell*)object;
            currentX = QPoint(QCursor::pos() - currentHeader->mapToGlobal(QPoint(0,0))).x();
        }
        else if(event->type() == QEvent::MouseMove) {
            TableCell *currentHeader = (TableCell*)object;
            if(startResize > -1) {
                int pointX = QPoint(QCursor::pos() - currentHeader->mapToGlobal(QPoint(0,0))).x();
                int delta = pointX - currentX;
                currentX = pointX;
                TableCell *resizeObject = 0;
                resizeObject = currentHeader;
                int width = resizeObject->width() + delta;
                resizeObject->setFixedWidth(width);
                resizeColumn(currentHeader->col(), width);
                adjustSize();
                return QFrame::eventFilter(object, event);
            }
            QPoint currentPos = QCursor::pos() - currentHeader->mapToGlobal(QPoint(0,0));
            if(currentPos.x() > currentHeader->width() - LIMIT_RESIZE) {
                currentHeader->setCursor(Qt::SizeHorCursor);
                inLimitZone = listHeader.indexOf(currentHeader);
            }
            else {
                currentHeader->setCursor(Qt::PointingHandCursor);
                inLimitZone = -1;
            }
        }
    }
    return QFrame::eventFilter(object, event);
}

void TinyTableWidget::resizeEvent(QResizeEvent *event)
{
    scrollArea->setFixedSize(event->size());
    verScrollBar->setSpace(0, scrollArea->height());
    verScrollBar->update(true);

    horScrollBar->setSpace(0, scrollArea->width());
    horScrollBar->update(true);
}

void TinyTableWidget::onDataChanged()
{

}

void TinyTableWidget::onUpdateSize(int row, int col, QSize size)
{
    resizeColumn(col, size.width());
    resizeRow(row, size.height());
}

void TinyTableWidget::onVerScrollValueChanged(int value)
{
    verScrollBar->setValue(value);
}

void TinyTableWidget::onHorScrollValueChanged(int value)
{
    horScrollBar->setValue(value);
}

void TinyTableWidget::initUI()
{
    scroll = new QWidget;
    scroll->setObjectName("TransWg");
    scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignTop);
    scrollArea->setFocusPolicy(Qt::NoFocus);
    scrollArea->setWidget(scroll);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    connect(scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onVerScrollValueChanged(int)));
    connect(scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onHorScrollValueChanged(int)));

    verScrollBar = new VerticalScrollbar(scrollArea, scrollArea->verticalScrollBar());
    verScrollBar->setMargin(0);
    verScrollBar->update(true);
    verScrollBar->setMinHeight(30);

    horScrollBar = new HorizontalScrollBar(scrollArea, scrollArea->horizontalScrollBar());
    horScrollBar->setMargin(0);
    horScrollBar->update(true);
    horScrollBar->setMinWidth(30);
    horScrollBar->setHeight(6);

    if(!mainLayout) {
        mainLayout = new QGridLayout(scroll);
        mainLayout->setSpacing(0);
        mainLayout->setMargin(0);
        mainLayout->setAlignment(Qt::AlignTop);
    }
}

void TinyTableWidget::resizeColumn(int index, int width)
{
    QMap<int, QMap<int, TableCell*> >::iterator it;
    for(it = mapCells.begin(); it != mapCells.end(); it++) {
        QMap<int, TableCell*> col = it.value();
        TableCell *cell = col.value(index, 0);
        if(!cell) continue;
        cell->setFixedWidth(width);
    }
}

void TinyTableWidget::resizeRow(int index, int height)
{
    QMap<int, TableCell*> col = mapCells.value(index);
    QMap<int, TableCell*>::iterator it;
    for(it = col.begin(); it != col.end(); it++) {
        it.value()->setFixedHeight(height);
    }
}

void TinyTableWidget::cacheCell(TableCell *cell)
{
    if(listCells.contains(cell)) return;
    listCells.append(cell);
}

void TinyTableWidget::cacheOldCells()
{
    QMap<int, QMap<int, TableCell*> >::iterator itRow;
    for(itRow = mapCells.begin(); itRow != mapCells.end(); itRow++) {
        QMap<int, TableCell*> rowMap = itRow.value();
        QMap<int, TableCell*>::iterator itCol;
        for(itCol = rowMap.begin(); itCol != rowMap.end(); itCol++) {
            TableCell *cell = itCol.value();
            if(cell) {
                cacheCell(cell);
                cell->hide();
            }
        }
    }
}

TableCell *TinyTableWidget::getCell()
{
    TableCell *cell = 0;
    if(!listCells.isEmpty()) {
        cell = listCells.last();
        listCells.removeLast();
    }
    if(!cell) {
        return new TableCell;
    }
    return cell;
}


