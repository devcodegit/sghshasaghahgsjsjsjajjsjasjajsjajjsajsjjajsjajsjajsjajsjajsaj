#ifndef STABLEVIEW_H
#define STABLEVIEW_H

#include <QWidget>

class QQuickWidget;

class STableView : public QWidget
{
    Q_OBJECT
public:
    explicit STableView(QWidget *parent = 0);
    void addData();

signals:

public slots:

private:
    QQuickWidget *view;
};

#endif // STABLEVIEW_H
