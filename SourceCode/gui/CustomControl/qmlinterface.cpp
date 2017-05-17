#include "qmlinterface.h"

QMLInterface *QMLInterface::Instance = 0;
QMLInterface::QMLInterface()
{

}

void QMLInterface::setData()
{
    emit setModelData();
}
