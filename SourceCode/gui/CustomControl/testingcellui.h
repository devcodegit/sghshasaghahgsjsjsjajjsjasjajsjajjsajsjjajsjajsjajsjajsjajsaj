#ifndef TESTINGCELLUI_H
#define TESTINGCELLUI_H

#include <QMetaType>
#include <QWidget>

class QPainter;

class TestingCellUI : public QWidget
{
    Q_OBJECT
public:
    explicit TestingCellUI(QWidget *parent = 0);

private:
};
#endif // TESTINGCELLUI_H
