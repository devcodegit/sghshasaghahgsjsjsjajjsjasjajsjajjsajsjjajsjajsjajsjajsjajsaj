#include "verticalscrollbar.h"

#include <QMouseEvent>
#include <QDebug>
#include <QScrollBar>
#include "../../style-sheet-manager.h"

VerticalScrollbar::VerticalScrollbar(QWidget *parent, QScrollBar *sampleScrollbar) :
    QFrame(parent)
{
#ifdef Q_OS_MAC
    isMousePress = false;
#endif
    isForceState = false;
    isHidden = false;
    lastPos = 0;
    from = 0;
    to = parent->height();
    widthBg = 0;
    _width = 6;
    height = 20;
    height_min = 20;
    margin = 8;
    min = 0;
    max = 0;
    resize(_width, to - from);
    thumb = new QFrame(this);
    thumb->resize(_width, height);
    thumb->setObjectName("VerticalScroll_Thumb");
    thumb->installEventFilter(this);
    setValue(0);
//    setStyleSheet("background-color: transparent;");
    setObjectName("VerticalScroll");

    connect(sampleScrollbar, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
    connect(sampleScrollbar, SIGNAL(rangeChanged(int,int)), this, SLOT(setRange(int,int)));
    connect(this, SIGNAL(valueChanged(int)), sampleScrollbar, SLOT(setValue(int)));
}

void VerticalScrollbar::mousePressEvent(QMouseEvent *event)
{
    int value_new = value + (to - from) * (event->pos().y() <= thumb->y() ? -1 : 1);
    if (value_new < min) value_new = min;
    else if (value_new > max) value_new = max;
    emit valueChanged(value_new);
    QFrame::mousePressEvent(event);
}

void VerticalScrollbar::mouseReleaseEvent(QMouseEvent *event)
{
    QFrame::mouseReleaseEvent(event);
}

void VerticalScrollbar::mouseMoveEvent(QMouseEvent *event)
{
    QFrame::mouseMoveEvent(event);
}

void VerticalScrollbar::enterEvent(QEvent *)
{
//    setStyleSheet("background: rgba(0,0,0,10%); border-radius: 4; border: 0px;");
    if (!isForceState)
        StyleSheetManager::changeProperty(this, "State", "Enter");
}

void VerticalScrollbar::leaveEvent(QEvent *)
{
#ifdef Q_OS_MAC
    if (!isMousePress) {
        //setStyleSheet("background-color: transparent;");
        StyleSheetManager::changeProperty(this, "State", "Leave");
    }
#endif
#ifdef Q_OS_WIN32
//    setStyleSheet("background-color: transparent;");
    if (!isForceState)
        StyleSheetManager::changeProperty(this, "State", "Leave");
#endif
}

bool VerticalScrollbar::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == thumb) {
        if (ev->type() == QEvent::MouseMove) {
            QMouseEvent *event = (QMouseEvent*)ev;
            if (event->buttons().testFlag(Qt::LeftButton)) {
                int yNew = thumb->y() + event->pos().y() - lastPos;
                if (yNew < from) yNew = /*from*/0;
                else if (yNew > to - height) yNew = to - height;
                int value_new = to - height - from == 0 ? 0 : yNew * (max - min) / (to - height - from);
                emit valueChanged(value_new);
            }
            return true;
        }
        else if (ev->type() == QEvent::MouseButtonPress) {
            QMouseEvent *event = (QMouseEvent*)ev;
            if (event->buttons().testFlag(Qt::LeftButton)) {
#ifdef Q_OS_MAC
                isMousePress = true;
#endif
//                thumb->setStyleSheet("background: rgba(0,0,0,30%); border-radius: 4");
                if (!isForceState)
                {
                    StyleSheetManager::changeProperty(thumb, "State", "Press");
                }
                else
                {
                    StyleSheetManager::changeProperty(thumb, "State", "PhotoViewPress");
                }
                lastPos = event->pos().y();
                emit onMousePress();
            }
            return true;
        }
        else if (ev->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *event = (QMouseEvent*)ev;
            if (!event->buttons().testFlag(Qt::LeftButton)) {
#ifdef Q_OS_MAC
                isMousePress = false;
#endif
//                thumb->setStyleSheet("background: rgba(0,0,0,20%); border-radius: 4");
                if (!isForceState)
                {
                    StyleSheetManager::changeProperty(thumb, "State", "Release");
                }
                else
                {
                    StyleSheetManager::changeProperty(thumb, "State", "PhotoViewRelease");
                }
                emit onMouseRelease();
            }
            return true;
        }
    }
    return QFrame::eventFilter(obj, ev);
}

void VerticalScrollbar::recalcHeight()
{
    int height_new = max == min ? height : (to - from) - (max - min);
    if (height_new != height) {
        if (height_new < height_min) {
            height = height_min;
        }
        else {
            height = height_new;
        }
        resize((widthBg > 0) ? widthBg : _width, to - from);
        thumb->resize(_width, height);
    }
}

void VerticalScrollbar::setSpace(int from, int to)
{    
    this->from = from;
    this->to = to;
    recalcHeight();
    update();
}

void VerticalScrollbar::setStyleBg()
{
    isForceState = true;
    StyleSheetManager::changeProperty(this, "State", "PhotoView");
    StyleSheetManager::changeProperty(thumb, "State", "PhotoView");
}

void VerticalScrollbar::setWidthBg(int width)
{
    widthBg = width;
    resize(width, to - from);
}

void VerticalScrollbar::setWidth(int width)
{
    this->_width = width;
    resize((widthBg > 0) ? widthBg : width, to - from);
    thumb->resize(width, height);
    update();
}

void VerticalScrollbar::setMinHeight(int height_min)
{
    this->height_min = height_min;
    if (height < height_min) {
        height = height_min;
        thumb->resize(_width, height);
        update();
    }
}

void VerticalScrollbar::setMargin(int margin)
{
    this->margin = margin;
    update();
}

void VerticalScrollbar::setRange(int min, int max)
{    
    this->min = min;
    this->max = max;
    recalcHeight();
    update();
}

void VerticalScrollbar::setValue(int value)
{
    this->value = value;
    if (this->value < min) this->value = min;
    else if (this->value > max) this->value = max;
    if (max == min) {
        hide();
    }
    else {
        int xPos = (this->width() - thumb->width()) / 2;
        int yPos = (this->value  * (to - height - from)) / (max - min);
        thumb->move(xPos, yPos);
        if (!isHidden) {
            show();
            raise();
            QFrame::update();
            parentWidget()->update();
        }
    }
}

void VerticalScrollbar::update(bool show)
{
    if (show) {
        isHidden = false;
        if (!isForceState)
            StyleSheetManager::changeProperty(this, "State", "Leave");
    }
    else {
        isHidden = true;
#ifdef Q_OS_MAC
        if (!isMousePress) {
           hide();
        }
#endif
#ifdef Q_OS_WIN32
        hide();
#endif
    }
    update();
}

void VerticalScrollbar::update()
{
    setGeometry(parentWidget()->width() - width() - margin, from, width(), to - from);
    setValue(value);
}

bool VerticalScrollbar::isMax(int diff)
{
    return value >= max - diff;
}

bool VerticalScrollbar::isMin(int diff)
{
    return value <= min + diff;
}

int VerticalScrollbar::getDiff(bool fromMaxNotMin)
{
    if (fromMaxNotMin) {
        return max - value;
    }
    return value - min;
}

int VerticalScrollbar::getValue()
{
    return value;
}
