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
    int width = 0;
    for(int i = 0; i < headers.length(); i++) {
        bool result = false;
        TableCell *headerItem = getCell(i, result);
        headerItem->setParent(this->scroll);
        headerItem->setCursor(Qt::PointingHandCursor);
        headerItem->setMouseTracking(true);
        headerItem->installEventFilter(this);
        headerItem->setFixedHeight(ROW_HEIGHT);
        headerItem->setIndex(0, i);
        headerItem->setText(headers.at(i), true);
        headerItem->adjustSize();
        if(listCellWidget.isEmpty()) {
            headerItem->move(0,0);
        }
        else {
            TableCell *pre = listCellWidget.last();
            headerItem->move(pre->x() + pre->width(), 0);
        }
        headerItem->show();
        if(!result) listCellWidget.append(headerItem);
        width += headerItem->width();
    }
    this->scroll->setFixedSize(width, ROW_HEIGHT);
    headerHeight = ROW_HEIGHT;
    colCount = headers.length();
}

void TinyTableWidget::setData(QList<QList<DataHandler::data_handler *> > data)
{
    rowCount = data.length();
    int totalHeight = 0;
    qDebug () << "setData#2";
    for(int row = 0; row < data.length(); row++) {
        for(int col = 0; col < data.at(row).length(); col++) {
            bool result = false;
            TableCell* cell = getCell((row + 1) * colCount + col, result);
            cell->setParent(this->scroll);
            cell->setData(data.at(row).at(col));
            cell->setCursor(Qt::PointingHandCursor);
            cell->installEventFilter(this);
            cell->setFixedHeight(100);
            cell->setIndex(row+1, col);
//            connect(cell, SIGNAL(updateSize(int,int,QSize)), this, SLOT(onUpdateSize(int,int,QSize)));

            TableCell *preTop = 0, *preLeft = 0;
            int x = 0, y = 0;
            if(!listCellWidget.isEmpty()) {
                preTop = listCellWidget.at(row * colCount + col);
                if(col <= 0) {
                    x = 0;
                }
                else {
                    preLeft = listCellWidget.at(row * colCount + col - 1);
                    x = preLeft->x() + preLeft->width();
//                    cell->setFixedHeight(preLeft->height());
                }
                y = preTop->y() + preTop->height();
                cell->setFixedWidth(preTop->width());
            }
            cell->move(x, y);
            cell->show();
            if(!result) listCellWidget.append(cell);

        }
        totalHeight += 100;
    }
    this->scroll->setFixedHeight(totalHeight + headerHeight);
    qDebug () << "setData#end" << this->scroll->size();
}

bool TinyTableWidget::eventFilter(QObject *object, QEvent *event)
{
    if(!listCellWidget.isEmpty() && listCellWidget.contains((TableCell*)object)) {
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
                int oldWidth = resizeObject->width();
                int width = resizeObject->width() + delta;
                resizeObject->setFixedWidth(width);
                resizeColumn(currentHeader->col(), width, oldWidth);
                adjustSize();
                return QFrame::eventFilter(object, event);
            }
            QPoint currentPos = QCursor::pos() - currentHeader->mapToGlobal(QPoint(0,0));
            if(currentPos.x() > currentHeader->width() - LIMIT_RESIZE) {
                currentHeader->setCursor(Qt::SizeHorCursor);
                inLimitZone = listCellWidget.indexOf(currentHeader) % colCount;
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
//    resizeColumn(col, size.width());
//    resizeRow(row, size.height());
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
}

void TinyTableWidget::resizeColumn(int index, int width, int oldWidth)
{
    if(listCellWidget.isEmpty()) return;
    for(int i = 0; i < listCellWidget.length(); i++) {
        TableCell *cell = listCellWidget.at(i);
        if(cell->col()  ==  index) {
            cell->setFixedWidth(width);
        }
        else if(cell->col() < index) continue;
        else {
            cell->move(cell->x() + (width - oldWidth), cell->y());
        }
    }
    this->scroll->setFixedWidth(this->scroll->width() + (width - oldWidth));
}

void TinyTableWidget::resizeRow(int index, int height, int oldHeight)
{

}

void TinyTableWidget::cacheCell(TableCell *cell)
{
}

void TinyTableWidget::cacheOldCells()
{

}

TableCell *TinyTableWidget::getCell(int index, bool &result)
{
    if(index >= listCellWidget.length()) {
        result = false;
        return new TableCell;
    }
    TableCell *cell = listCellWidget.at(index);
    result = true;
    return cell;
}

void TinyTableWidget::generateCellPos()
{

}


