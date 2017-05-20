#include "uimodel.h"

UIModel *UIModel::Instance = 0;
UIModel::UIModel()
{

}

void UIModel::setMainWindow(QWidget *widget)
{
    this->mainWindow = widget;
}

QWidget *UIModel::getMainWindow()
{
    return this->mainWindow;
}
