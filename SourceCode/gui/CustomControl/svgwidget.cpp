#include "svgwidget.h"
#include <QHBoxLayout>

SvgWidget::SvgWidget(QWidget *parent, QString imageNormal, QString imageHover, QString styleFocus, QString imageDisabled) :
    QSvgWidget(parent)
{
    this->imageNormal = imageNormal;
    this->imageHover = imageHover;
    this->styleFocus = styleFocus;
    this->imageDisabled = imageDisabled;
    m_isDisabled = false;
    m_isMousePress = false;
    frameFocus = NULL;
    leaveEvent(0);
}

void SvgWidget::setImageNormal(QString imageName)
{
    this->imageNormal = imageName;
    if(!this->imageNormal.isEmpty())
    {
        load(imageNormal);
    }
}

void SvgWidget::setImageHover(QString imageName)
{
    this->imageHover = imageName;
//    if(!this->imageHover.isEmpty())
//    {
//        load(imageNormal);
    //    }
}

void SvgWidget::setImageDisable(QString imageName)
{
    this->imageDisabled = imageName;
}

void SvgWidget::setStyleNormal()
{
    load(imageNormal);
}

void SvgWidget::setStyleHover()
{
    load(imageHover);
}

void SvgWidget::setDisabled(bool disabled)
{
    m_isDisabled = disabled;
    if (m_isDisabled) {
        load(imageDisabled);
    }
    else {
        load(imageNormal);
    }
}

void SvgWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (!m_isDisabled) {
            x1 = event->x();
            y1 = event->y();
            m_isMousePress = true;
        }
        return;
    }
    QSvgWidget::mousePressEvent(event);
}

void SvgWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (m_isMousePress) {
            m_isMousePress = false;
            if (event->x() >= 0 && event->x() <= this->width() && event->y() >= 0 && event->y() <= this->height()) {
                if (!m_isDisabled) emit onClicked();
            }
            return;
        }
    }
    QSvgWidget::mouseReleaseEvent(event);
}

void SvgWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (x1 != event->x() || y1 != event->y()) {
            if (!m_isDisabled) emit onDrag();
            return;
        }
    }
//    QSvgWidget::mouseMoveEvent(event);
}

void SvgWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    emit onEnter();
    if (!m_isDisabled && !imageHover.isEmpty()) {
        load(imageHover);
    }
}

void SvgWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    emit onLeave();
    if (!m_isDisabled && !imageNormal.isEmpty()) {
        load(imageNormal);
    }

}

void SvgWidget::focusInEvent(QFocusEvent *ev)
{
    if (!styleFocus.isEmpty()) {
        if (!frameFocus) {
            frameFocus = new QFrame;
            frameFocus->setStyleSheet(styleFocus);
            QHBoxLayout *layout = new QHBoxLayout(this);
            layout->setMargin(0);
            layout->addWidget(frameFocus);
        }
        frameFocus->show();
    }
    QSvgWidget::focusInEvent(ev);
}

void SvgWidget::focusOutEvent(QFocusEvent *ev)
{
    if (!styleFocus.isEmpty()) {
        if (frameFocus) {
            frameFocus->hide();
        }
    }
    QSvgWidget::focusOutEvent(ev);
}
