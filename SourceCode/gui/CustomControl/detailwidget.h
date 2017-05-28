#ifndef DETAILWIDGET_H
#define DETAILWIDGET_H

#include <QWidget>
#include "sdialog.h"

namespace Core {
    namespace DataItem {
        class LazadaDataItemOrder;
    }
}
class QLabel;
class QScrollArea;
class VerticalScrollbar;

using namespace Core::DataItem;

class DetailWidget : public SDialog
{
    Q_OBJECT
public:
    struct detail_data {

    };

    explicit DetailWidget(QWidget *parent = 0);
    void setData(LazadaDataItemOrder *data);

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
