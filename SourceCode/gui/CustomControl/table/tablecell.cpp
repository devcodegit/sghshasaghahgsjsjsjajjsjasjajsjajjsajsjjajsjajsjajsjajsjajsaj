#include "tablecell.h"
#include "../../../style-sheet-manager.h"
#include "../../../signalsender.h"
#include <QLabel>
#include <QCheckBox>
#include <QPixmap>
#include <QDebug>
#include <QBoxLayout>


TableCell::TableCell(QWidget *parent) : QFrame(parent)
{
    initUI();
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
    if(row % 2 == 0) {
        currentState = "Event";
    }
    else {
        currentState = "";
    }
    StyleSheetManager::changeProperty(this, "row", currentState);
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

void TableCell::setActive(bool isActive)
{
    this->isActive = isActive;
}

bool TableCell::active()
{
    return this->isActive;
}

void TableCell::setText(const QString &title, bool isHeader)
{
    if(isHeader) {
        currentState = "Header";
    }
    StyleSheetManager::changeProperty(this, "row", currentState);
    this->ensurePolished();
    if(!this->title) {
        this->title = new QLabel;
        layout->addWidget(this->title);
    }
    this->title->setText(title);
    this->title->show();
}

void TableCell::setImage(const QString &url)
{
    if(!this->thumb) {
        this->thumb = new QLabel;
        layout->addWidget(this->thumb);

    }
    this->thumb->setPixmap(QPixmap(url).scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    this->thumb->show();
}

void TableCell::setCheckbox(bool isChecked)
{
    if(!this->checkbox) {
        this->checkbox = new QCheckBox;
        layout->addWidget(this->checkbox);
    }
    this->checkbox->setChecked(isChecked);
    this->checkbox->show();
}

void TableCell::setDropDown(QStringList item)
{
    if(!this->moreItem) {
        this->moreItem = new MoreItem;
        layout->addWidget(this->moreItem);
    }
}

void TableCell::setMore(int moreId)
{
    this->moreItem->setId(moreId);
    this->moreItem->show();
}

void TableCell::initUI()
{
    setObjectName("TableCell");
    layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
}

MoreItem::MoreItem(QWidget *parent) : SvgWidget(parent, QString(":/Icon/Image/more_button.svg"))
{
    setFixedSize(20, 20);
    connect(this, SIGNAL(onClicked()), this, SLOT(onRequestMore()));
}

void MoreItem::setId(int id)
{
    this->_id = id;
}

int MoreItem::id()
{
    return this->_id;
}

void MoreItem::onRequestMore()
{
    emit SignalSender::instance()->showMoreInfo(this->_id);
}
