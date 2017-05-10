#ifndef SWIDGET_H
#define SWIDGET_H

#include <QWidget>

class SWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SWidget(QWidget *parent = 0);
    void setObject(const QString style);

signals:

public slots:
};

#endif // SWIDGET_H
