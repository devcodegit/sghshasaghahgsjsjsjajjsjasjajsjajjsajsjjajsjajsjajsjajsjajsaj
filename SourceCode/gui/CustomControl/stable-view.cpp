#include "stable-view.h"
#include "qmlinterface.h"
#include <QtQuick>
#include <QQuickWidget>

STableView::STableView(QWidget *parent) : QWidget(parent)
{
    view = new QQuickWidget(this);
    view->engine()->rootContext()->setContextProperty("QMLInterface", QMLInterface::instance());
    view->setSource(QUrl("qrc:/qml/search_table.qml"));
    view->setResizeMode(QQuickWidget::SizeRootObjectToView);
    view->show();
}

void STableView::addData()
{
    QMLInterface::instance()->setData();
}
