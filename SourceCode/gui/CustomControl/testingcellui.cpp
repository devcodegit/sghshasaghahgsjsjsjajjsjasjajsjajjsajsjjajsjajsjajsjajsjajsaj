#include "testingcellui.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>

TestingCellUI::TestingCellUI(QWidget *parent) : QWidget(parent)
{
    QLabel *label = new QLabel(this);
    label->show();
}
