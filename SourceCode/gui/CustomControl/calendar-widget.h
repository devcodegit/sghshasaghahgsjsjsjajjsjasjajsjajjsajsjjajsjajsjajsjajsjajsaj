#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QList>
#include <QVector>
#include <QDate>
#include "zbackground-menu.h"

class QPushButton;
class QLabel;

class CalendarItem : public QLabel
{
    Q_OBJECT
public:
    explicit CalendarItem(QWidget *parent = 0);
    void setYear(int number, bool isCurrent = true);
    void setDay(QDate _date, bool isCurrent = true);
    void setMonthStr(int _month, bool isCurrent = true);
    void setEnabled(bool enable);

    QDate date() {return _date;}

protected:
    virtual void mousePressEvent(QMouseEvent *event);

signals:
    void clicked(QDate _date);
    void clicked(int _month);

private:
    enum State {
        DAY,
        MONTH,
        YEAR
    };

    QDate _date;
    int _month;
    int _year;
    State _state = DAY;
    bool _enable = true;

private:

};

class CalendarWidget : public ZBackgroundMenu
{
    Q_OBJECT
public:

    enum DateViewState {
        MONTH,
        YEAR,
        YEAR12
    };

    explicit CalendarWidget(QWidget *parent = 0, bool startByDate = true);
    void setMaximumDate(QDate date);
    void setMinimumDate(QDate date);
    void resetDate();
    void setSelectedDate(QDate date);

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void showEvent(QShowEvent *event);

signals:
    void clicked(QDate date);

public slots:
private slots:
    void onClickedDate(QDate date);
    void onClickedMonth(int month);
    void onClickedYear(int year);
    void onClickedTitle();
    void generateDayInMonth(int year, int month, int wheel = 0);
    void generateYearInDecade(int year);
    void onNextClicked();
    void onPreviousClicked();
    void onNext(bool isWheel = false);
    void onPrevious(bool isWheel = false);

private:
    QVector<CalendarItem*> _listDay = QVector<CalendarItem*>();
    QVector<CalendarItem*> _listYear = QVector<CalendarItem*>();
    QPushButton *_title = NULL;
    QFrame *_frameMonth = NULL, *_frameYear = NULL, *_frameDecade = NULL, *_mainFrame = NULL;
    QLabel *lblSun,*lblMon,*lblTue,*lblWed,*lblThu,*lblFri,*lblSat;
    DateViewState _state = MONTH;
    QDate _maximumDate, _minimumDate;
    int _currentYear, _currentMonth, _currentDay;
    int _wheelCount = 0;
    QDate _selectedDate;
    bool startByDate = true;

private:
    void showCalendar(DateViewState _state);
    bool validDate();
};

#endif // CALENDARWIDGET_H
