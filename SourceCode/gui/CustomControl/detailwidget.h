#ifndef DETAILWIDGET_H
#define DETAILWIDGET_H

#include <QWidget>
#include "sdialog.h"

namespace Lazada { namespace DataModel {
    class DataOrder;
}}
class QLabel;
class QScrollArea;
class VerticalScrollbar;

using namespace Lazada::DataModel;

class DetailWidget : public SDialog
{
    Q_OBJECT
public:

    explicit DetailWidget(QWidget *parent = 0);
    void setData(DataOrder *data);

signals:

public slots:

private slots:
    void onScrollValueChanged(int value);

private:
    QLabel *label = 0;
    QScrollArea *scrollArea;
    VerticalScrollbar *scrollBar;
    QWidget *scroll;
};

#endif // DETAILWIDGET_H
