#include "sbuttonoption.h"

#include <QLabel>
#include <QSvgWidget>

SButtonOption::SButtonOption(QWidget *parent) : QPushButton(parent)
{
    _plbText = new QLabel();
    _pIcon = new QSvgWidget();
    _pIcon->load(QString(":/Icon/Image/arrow-point-to-right.svg"));
    _pIcon->setFixedSize(20,20);
}

void SButtonOption::setText(const QString &text)
{
    if (_plbText)
    {
        _plbText->setText(text);
    }
}

void SButtonOption::resizeEvent(QResizeEvent *ev)
{
    Q_UNUSED(ev);

    if (_pIcon)
    {
//        _pIcon->move(width() - _pIcon->width() - 10, );
    }
}
