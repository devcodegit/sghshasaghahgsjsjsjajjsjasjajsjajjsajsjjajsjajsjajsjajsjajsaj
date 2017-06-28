#include "horizontalscrollbar.h"
#include <QMouseEvent>
#include <QScrollBar>
#include "../../style-sheet-manager.h"

HorizontalScrollBar::HorizontalScrollBar(QWidget *parent, QScrollBar *sampleScrollBar) :
    QFrame(parent)
{
    isHidden = false;
    lastPos = 0;
    from = 0;
    to = parent->width();
    width = 20;
    width_min = 20;
    height = 6;
    margin = 8;
    min = 0;
    max = 0;
    resize(width, height);
    setValue(0);
    setObjectName("HorizontalScrollBar");

    connect(sampleScrollBar, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
    connect(sampleScrollBar, SIGNAL(rangeChanged(int,int)), this, SLOT(setRange(int,int)));
    connect(this, SIGNAL(valueChange(int)),sampleScrollBar, SLOT(setValue(int)));
}

void HorizontalScrollBar::setSpace(int from, int to)
{
    this->from = from;
    this->to = to;
    recalcWidth();
    update();
}

void HorizontalScrollBar::setHeight(int height)
{
    this->height = height;
    resize(width,height);
    update();
}

void HorizontalScrollBar::setMinWidth(int width_min)
{
    this->width_min = width_min;
    if (width < width_min) {
        width = width_min;
        resize(width,height);
        update();
    }
}

void HorizontalScrollBar::setMargin(int margin)
{
    this->margin = margin;
    update();
}

void HorizontalScrollBar::update(bool show)
{
    if (show) {
        isHidden = false;
    }
    else {
        isHidden = true;
        hide();
    }
    update();
}

void HorizontalScrollBar::update()
{
    setValue(value);
}

bool HorizontalScrollBar::isMin(int diff)
{
    return value <= min + diff;
}

bool HorizontalScrollBar::isMax(int diff)
{
    return value >= max - diff;
}

int HorizontalScrollBar::getDiff(bool fromMaxNotMin)
{
    if (fromMaxNotMin) {
        return max - value;
    }
    return value - min;
}

int HorizontalScrollBar::getValue()
{
    return value;
}

void HorizontalScrollBar::setRange(int min, int max)
{
    this->min = min;
    this->max = max;
    recalcWidth();
    update();
}

void HorizontalScrollBar::setValue(int value)
{
    this->value = value;
    if (this->value < min) {
        this->value = min;
    }
    else if (this->value > max) {
        this->value = max;
    }

    if (min == max) {
        hide();
    }
    else {
        move((this->value * (to - width - from)) / (max - min) + from, parentWidget()->height() - height - margin);
        if (!isHidden) {
            show();
            raise();
            parentWidget()->update();
        }
    }
}

void HorizontalScrollBar::mousePressEvent(QMouseEvent *ev)
{
    if (ev->buttons().testFlag(Qt::LeftButton)) {
        StyleSheetManager::changeProperty(this, "State", "Pressed");
        lastPos = ev->pos().x();
    }
}

void HorizontalScrollBar::mouseReleaseEvent(QMouseEvent *ev)
{
    if (!ev->buttons().testFlag(Qt::LeftButton)) {
        StyleSheetManager::changeProperty(this, "State", "");
    }
}

void HorizontalScrollBar::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons().testFlag(Qt::LeftButton)) {
        int xNew = x() + ev->pos().x() - lastPos;
        if (xNew < from) {
            xNew = from;
        }
        else if (xNew > to - width) {
            xNew = to - width;
        }
        int value_new = to - width - from == 0 ? 0 : xNew * (max - min) / (to - width - from);
        emit valueChange(value_new);
    }
}

void HorizontalScrollBar::recalcWidth()
{
    int width_new = max == min ? width : (to - from) - (max - min);
    if (width_new != width) {
        if (width_new < width_min) {
            width = width_min;
        }
        else {
            width = width_new;
        }
        resize(width,height);
    }
}
