#ifndef DATERANGEWIDGET_H
#define DATERANGEWIDGET_H

#include <QFrame>
#include <QDate>

class QLabel;

class DateRangeWidget : public QFrame
{
    Q_OBJECT
public:
    explicit DateRangeWidget(QWidget *parent = 0);
    void setStartDate(QDate date);
    void setEndDate(QDate date);
    void reset();


protected:
    virtual bool eventFilter(QObject *object, QEvent *event);

signals:
    void choose(bool isStartDate, QDate dateTime);
public slots:

private:
    QLabel *dateStartLbl = 0, *dateEndLbl = 0;
    QDate startDate, endDate;
private:
    void onStartClicked();
    void onEndClicked();
};

#endif // DATERANGEWIDGET_H
