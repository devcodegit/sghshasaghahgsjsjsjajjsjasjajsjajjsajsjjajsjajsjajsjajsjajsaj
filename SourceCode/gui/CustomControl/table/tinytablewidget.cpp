#include "tinytablewidget.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <QEvent>
#include <QApplication>
#include <QCheckBox>
#include <QPixmap>

#define HEADER_HEIGHT 50
#define ROW_HEIGHT 50
#define ROW_WIDTH 150
#define LIMIT_RESIZE 5

TinyTableWidget::TinyTableWidget(QWidget *parent) : QFrame(parent)
{
    setFixedHeight(HEADER_HEIGHT);
    setStyleSheet("border: 1px dashed green;");
    initLayout();
}

void TinyTableWidget::setHeader(QStringList headers)
{
    listHeader.clear();
    for(int i = 0; i < headers.length(); i++) {
        TableCell *headerItem = new TableCell(headers.at(i));
        headerItem->setCursor(Qt::PointingHandCursor);
        headerItem->setMouseTracking(true);
        headerItem->installEventFilter(this);
        headerItem->setStyleSheet("border: 1px solid red;");
        headerItem->setFixedHeight(ROW_HEIGHT);
        headerItem->setIndex(0, i);
        mainLayout->addWidget(headerItem, 0, i, 1, 1);
        listHeader.append(headerItem);
    }
}

void TinyTableWidget::setData(DataHandler *data)
{
    QList<QList<DataHandler::data_handler *> > _data = data->getData();
    rowCount = _data.length();
    for(int row = 0; row < _data.length(); row++) {
        QMap<int, TableCell*> mapCols;
        int height = 0;
        for(int col = 0; col < _data.at(row).length(); col++) {
            TableCell* cell =  new TableCell;
            cell->setData(_data.at(row).at(col));
            cell->setCursor(Qt::PointingHandCursor);
            cell->installEventFilter(this);
            cell->setIndex(row, col); connect(cell, SIGNAL(updateSize(int,int,QSize)), this, SLOT(onUpdateSize(int,int,QSize)));
            mainLayout->addWidget(cell, row, col, 1, 1);
            mapCols.insert(col, cell);
            height = qMax(height, cell->height());
        }
        mapCells.insert(row, mapCols);
        this->setFixedHeight(height + this->height());
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

void TinyTableWidget::onDataChanged()
{

}

void TinyTableWidget::onUpdateSize(int row, int col, QSize size)
{
    resizeColumn(col, size.width());
    resizeRow(row, size.height());
}

void TinyTableWidget::initLayout()
{
    if(!mainLayout) {
        mainLayout = new QGridLayout(this);
        mainLayout->setSpacing(0);
        mainLayout->setMargin(0);
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


TableCell::TableCell(const QString &title, QWidget *parent) : QFrame(parent)
{
    layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    this->title = new QLabel;
    this->thumb = new QLabel;
    this->checkbox = new QCheckBox;
    this->moreItem = new MoreItem;
    layout->addWidget(this->checkbox);
    layout->addWidget(this->thumb);
    layout->addWidget(this->title);
    layout->addWidget(this->moreItem);
    this->title->hide();
    this->thumb->hide();
    this->checkbox->hide();
    this->moreItem->hide();

    if(!title.isEmpty()) {
        setText(title);
    }
}

void TableCell::setContent(QWidget *content)
{
    if(!content) return;
    content->setParent(this);
    content->move(0,0);
    content->show();
    this->setFixedSize(content->size());
}

void TableCell::setData(DataHandler::data_handler *data)
{
    if(!data) return;
    DataHandler::data_type type = data->type;
    switch(type) {
    case DataHandler::PLAINTEXT:
        setText(data->title);
        break;
    case DataHandler::PHOTO:
        setImage(data->thumbUrl);
        break;
    case DataHandler::CHECKBOX:
        setCheckbox(data->isChecked);
        break;
    case DataHandler::DROPDOWN:
    case DataHandler::MORE:
        setMore(data->moreId);
        break;
    default:
        break;
    }
}

void TableCell::setIndex(int row, int col)
{
    this->_row = row;
    this->_col = col;
}

void TableCell::reset()
{
    this->title->hide();
    this->thumb->hide();
    this->checkbox->hide();
    this->moreItem->hide();
}

int TableCell::row()
{
    return _row;
}

int TableCell::col()
{
    return _col;
}

void TableCell::setText(const QString &title)
{
    this->title->setText(title);
    this->title->show();
}

void TableCell::setImage(const QString &url)
{
    this->thumb->setPixmap(QPixmap(url).scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    this->thumb->show();
}

void TableCell::setCheckbox(bool isChecked)
{
    this->checkbox->setChecked(isChecked);
    this->checkbox->show();
}

void TableCell::setDropDown(QStringList item)
{

}

void TableCell::setMore(int moreId)
{
    this->moreItem->setId(moreId);
    this->moreItem->show();
}

MoreItem::MoreItem(QWidget *parent) : SvgWidget(parent, QString(":/Icon/Image/more_button.svg"))
{
    setFixedSize(20, 20);
}

void MoreItem::setId(int id)
{
    this->_id = id;
}

int MoreItem::id()
{
    return this->_id;
}
