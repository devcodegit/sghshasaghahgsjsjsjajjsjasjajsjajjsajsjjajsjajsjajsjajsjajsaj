#include "swidget.h"
#include <QDebug>
SWidget::SWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << "init";
}

void SWidget::setObject(const QString style)
{
    QWidget::setObjectName(style);
}
