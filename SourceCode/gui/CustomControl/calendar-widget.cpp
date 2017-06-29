#include "calendar-widget.h"
#include "../../style-sheet-manager.h"
#include "svgwidget.h"
#include <QPainter>
#include <QGridLayout>
#include <QDateTime>
#include <QPushButton>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QDebug>
#include <QLocale>

#define CALENDAR_ITEM_SIZE 20
#define WIDGET_WIDTH 294
#define WIDGET_HEIGHT (162+20)
#define TITLE_HEIGHT 24
#define TOPBOTTOM_MARGIN 8
#define LEFTRIGHT_MARGIN 16
#define CONTENT_WIDTH (WIDGET_WIDTH-2*LEFTRIGHT_MARGIN)
#define CONTENT_HEIGHT (WIDGET_HEIGHT-TITLE_HEIGHT-2*TOPBOTTOM_MARGIN)

CalendarWidget::CalendarWidget(QWidget *parent, bool startByDate) : ZBackgroundMenu(WIDGET_WIDTH, WIDGET_HEIGHT, parent), startByDate(startByDate)
{
    setObjectName("DatePickerBg");
    setFixedSize(WIDGET_WIDTH, WIDGET_HEIGHT);
    _minimumDate = QDate(1970, 1, 1);
    _maximumDate = QDate(2050, 12, 31);
    _selectedDate = QDate::currentDate();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(LEFTRIGHT_MARGIN,TOPBOTTOM_MARGIN,LEFTRIGHT_MARGIN,TOPBOTTOM_MARGIN);

    _mainFrame = new QFrame;
    _mainFrame->setFixedSize(CONTENT_WIDTH, CONTENT_HEIGHT);
    _mainFrame->move(0, 0);

    _frameMonth = new QFrame(_mainFrame);
    _frameMonth->setFixedSize(CONTENT_WIDTH, CONTENT_HEIGHT);
    _frameMonth->move(0, 0);
    QGridLayout *monthLayout = new QGridLayout(_frameMonth);
    monthLayout->setSpacing(0);
    monthLayout->setMargin(0);

    //create top panel
    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->setSpacing(0);
    titleLayout->setMargin(0);

    SvgWidget *previousButton = new SvgWidget(this, QString(":/Icon/Image/icon_back_8x14.svg"));
    previousButton->setFocusPolicy(Qt::NoFocus);
    previousButton->setFixedSize(8, 14);
    previousButton->setCursor(Qt::PointingHandCursor);
    connect(previousButton, SIGNAL(onClicked()), this, SLOT(onPreviousClicked()));
    SvgWidget *nextButton = new SvgWidget(this, QString(":/Icon/Image/icon_next_8x14.svg"));
    nextButton->setFocusPolicy(Qt::NoFocus);
    nextButton->setFixedSize(8, 14);
    nextButton->setCursor(Qt::PointingHandCursor);
    connect(nextButton, SIGNAL(onClicked()), this, SLOT(onNextClicked()));

    _title = new QPushButton;
    _title->setFocusPolicy(Qt::NoFocus);
    _title->setObjectName("DatePickerDayOfWeek");
    _title->resize(this->width(), TITLE_HEIGHT);
    _title->setCursor(Qt::PointingHandCursor);
    connect(_title, SIGNAL(clicked(bool)), this, SLOT(onClickedTitle()));

    titleLayout->addWidget(previousButton,0,Qt::AlignLeft);
    titleLayout->addWidget(_title,1,Qt::AlignCenter);
    titleLayout->addWidget(nextButton,0,Qt::AlignRight);

    lblSun = new QLabel("Sun");
    lblSun->setObjectName("DatePickerDayOfWeek");
    lblMon = new QLabel("Mon");
    lblMon->setObjectName("DatePickerDayOfWeek");
    lblTue = new QLabel("Tue");
    lblTue->setObjectName("DatePickerDayOfWeek");
    lblWed = new QLabel("Wed");
    lblWed->setObjectName("DatePickerDayOfWeek");
    lblThu = new QLabel("Thu");
    lblThu->setObjectName("DatePickerDayOfWeek");
    lblFri = new QLabel("Fri");
    lblFri->setObjectName("DatePickerDayOfWeek");
    lblSat = new QLabel("Sat");
    lblSat->setObjectName("DatePickerDayOfWeek");

    monthLayout->addWidget(lblSun, 1, 0, 1, 1, Qt::AlignCenter);
    monthLayout->addWidget(lblMon, 1, 1, 1, 1, Qt::AlignCenter);
    monthLayout->addWidget(lblTue, 1, 2, 1, 1, Qt::AlignCenter);
    monthLayout->addWidget(lblWed, 1, 3, 1, 1, Qt::AlignCenter);
    monthLayout->addWidget(lblThu, 1, 4, 1, 1, Qt::AlignCenter);
    monthLayout->addWidget(lblFri, 1, 5, 1, 1, Qt::AlignCenter);
    monthLayout->addWidget(lblSat, 1, 6, 1, 1, Qt::AlignCenter);

    // create matrix of days
    for(int i = 0; i < 42 /*7*6*/ ; i++) {
        CalendarItem *item = new CalendarItem;
        item->setAlignment(Qt::AlignCenter);
        connect(item, SIGNAL(clicked(QDate)), this, SLOT(onClickedDate(QDate)));
        monthLayout->addWidget(item, i / 7 + 2, i % 7, 1, 1);
        _listDay.append(item);
    }


    // create frame of months

    _frameYear = new QFrame(_mainFrame);
    _frameYear->setFixedSize(CONTENT_WIDTH, CONTENT_HEIGHT);
    _frameYear->move(0, 0);
    _frameYear->hide();
    QGridLayout *yearLayout = new QGridLayout(_frameYear);
    yearLayout->setSpacing(0);
    yearLayout->setMargin(0);

    for(int i = 0; i < /*16*/12; i++) {
        CalendarItem *item = new CalendarItem;
        item->setAlignment(Qt::AlignCenter);
        connect(item, SIGNAL(clicked(int)), this, SLOT(onClickedMonth(int)));
        yearLayout->addWidget(item, i  / 4, i % 4, 1, 1);
//        item->setMonthStr(i + 1 - ((i <= 11) ? 0 : 12), (i <= 11));
        item->setMonthStr(i + 1);
    }


    //create frame decade

    _frameDecade = new QFrame(_mainFrame);
    _frameDecade->setFixedSize(CONTENT_WIDTH, CONTENT_HEIGHT);
    _frameDecade->move(0, 0);
    _frameDecade->hide();

    QGridLayout *decadeLayout = new QGridLayout(_frameDecade);
    decadeLayout->setSpacing(0);
    decadeLayout->setMargin(0);

    for(int i = 0; i < 16; i++) {
        CalendarItem *item = new CalendarItem;
        item->setAlignment(Qt::AlignCenter);
        connect(item, SIGNAL(clicked(int)), this, SLOT(onClickedYear(int)));
        decadeLayout->addWidget(item, i  / 4, i % 4, 1, 1);
        _listYear.append(item);
    }


    /////////////////

    layout->addLayout(titleLayout);
    layout->addWidget(_mainFrame);
    resetDate();
}

void CalendarWidget::setMaximumDate(QDate date)
{
    this->_maximumDate = date;
}

void CalendarWidget::setMinimumDate(QDate date)
{
    this->_minimumDate = date;
}

void CalendarWidget::resetDate()
{
    QDate today = QDate::currentDate();
    if(_selectedDate != today) {
        setSelectedDate(_selectedDate);
        return;
    }
    _currentYear = today.year();
    _currentMonth = today.month();
    _currentDay = today.day();
    if(startByDate) {
        generateDayInMonth(_currentYear, _currentMonth);
        showCalendar(MONTH);
    }
    else {
        generateYearInDecade(_currentYear);
        showCalendar(YEAR12);
    }
}

void CalendarWidget::setSelectedDate(QDate date)
{
    if(date > _maximumDate || date < _minimumDate) return;
    _selectedDate = date;
    _currentDay = date.day();
    _currentMonth = date.month();
    _currentYear = date.year();
    if(startByDate) {
        generateDayInMonth(_selectedDate.year(), _selectedDate.month());
        showCalendar(MONTH);
    }
    else {
        generateYearInDecade(_selectedDate.year());
        showCalendar(YEAR12);
    }
}

void CalendarWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0) { // scroll up
        if(_state == MONTH) _wheelCount--;
        onPrevious(true);
    }
    else { // scroll down
        if(_state == MONTH) _wheelCount++;
        onNext(true);
    }
}

void CalendarWidget::showEvent(QShowEvent *event)
{
    (void)event;
    resetDate();
}

void CalendarWidget::onClickedDate(QDate date)
{
    qDebug () << "ClickedDate" << date;
    _currentDay = date.day();
    _currentMonth = date.month();
    _currentYear = date.year();
//    _selectedDate = date;
    emit clicked(date);
    close();
}

void CalendarWidget::onClickedMonth(int month)
{
    _currentMonth = month;
    _state = MONTH;
    showCalendar(_state);
    generateDayInMonth(_currentYear, _currentMonth);
}

void CalendarWidget::onClickedYear(int year)
{
    this->_currentYear = year;
    _state = YEAR;
    showCalendar(_state);
}

void CalendarWidget::onClickedTitle()
{
    switch(_state) {
    case MONTH:
        _state = YEAR;
        break;
    case YEAR:
        _state = YEAR12;
        generateYearInDecade(_currentYear);
        break;
    case YEAR12:
    default:
        break;
    }
    showCalendar(_state);
}

void CalendarWidget::generateDayInMonth(int year, int month, int wheel)
{
    _wheelCount = wheel;
    QString titleStr;
    QLocale _locale = QLocale(QLocale::Vietnamese, QLocale::Vietnam);
    titleStr = _locale.toString(QDate(year, month, 1), "MMMM yyyy");
    titleStr = titleStr.left(1).toUpper() + titleStr.mid(1);
   _title->setText(titleStr);
    QDate date;
    date.setDate(year, month, 1);
    int dayOfWeek = date.dayOfWeek() - wheel * 7;
    int previousMonth = ((month == 1) ? 12 : (month - 1));
    int nextMonth = ((month == 12) ? 1 : (month + 1));
    int previousYear = ((previousMonth == 12) ? (year - 1) : year);
    int nextYear = ((nextMonth == 1) ? (year + 1) : year);
    QDate preDate;
    preDate.setDate(year, previousMonth, 1);

    for(int i = 0; i < 42; i++) {
        if(i < dayOfWeek) {
            // previous month
            _listDay[i]->setDay(QDate(previousYear, previousMonth, preDate.daysInMonth() - dayOfWeek + i + 1), false);
        }
        else if (i >= dayOfWeek + date.daysInMonth()) {
            // next month
            _listDay[i]->setDay(QDate(nextYear, nextMonth, i - (dayOfWeek + date.daysInMonth()) + 1), false);
        }
        else {
            // current month
            _listDay[i]->setDay(QDate(year, month, i - dayOfWeek + 1));
            if(i - dayOfWeek + 1 == _selectedDate.day() && month == _selectedDate.month() && year == _selectedDate.year() && _selectedDate != QDate::currentDate()) {
                StyleSheetManager::changeProperty(_listDay[i], "State", "Selected");
            }
        }
        if(_listDay[i]->date() > _maximumDate || _listDay[i]->date() < _minimumDate) {
            _listDay[i]->setEnabled(false);
        }
        else {
            _listDay[i]->setEnabled(true);
        }
    }
}

void CalendarWidget::generateYearInDecade(int year)
{
    int yearBegin = (year / 10) * 10;
    int yearEnd = yearBegin + 9;
    _title->setText(QString("%1 - %2").arg(yearBegin).arg(yearEnd));
    int start = yearBegin - (yearBegin % 4) + 1 - ((yearBegin % 4 == 0) ? 4 : 0);
    int end = start + 16;
    for(int i = start; i < end; i++) {
        _listYear[i - start]->setYear(i, (i >= yearBegin && i <= yearEnd));
        if(i < _minimumDate.year() || i > _maximumDate.year()) {
            _listYear[i - start]->setEnabled(false);
        }
        else {
            _listYear[i - start]->setEnabled(true);
        }
    }
}

void CalendarWidget::onNextClicked()
{
    onNext(false);
}

void CalendarWidget::onPreviousClicked()
{
    onPrevious(false);
}

void CalendarWidget::onNext(bool isWheel)
{
    switch(_state) {
    case MONTH:
        if(isWheel && _currentMonth >= _maximumDate.month() && _currentYear >= _maximumDate.year() && _wheelCount == 1) {
            _wheelCount = 0;
            return;
        }
        if(_wheelCount >= 3) {
            _wheelCount = -1;
            _currentMonth++;
        }
        if(!isWheel) {
            _currentMonth++;
            _wheelCount = 0;
        }
        if(!validDate()) return;
        generateDayInMonth(_currentYear, _currentMonth, _wheelCount);
        break;
    case YEAR:
        if(QDate(_currentYear + 1, _currentMonth, _currentDay) > _maximumDate) return;
        _currentYear++;
        _title->setText(QString::number(_currentYear));
        break;
    case YEAR12:
        if(QDate(_currentYear + 9, _currentMonth, _currentDay) > _maximumDate) return;
        _currentYear += 10;
        generateYearInDecade(_currentYear);
    default:
        break;
    }
}

void CalendarWidget::onPrevious(bool isWheel)
{
    switch(_state) {
    case MONTH:
        if(isWheel && _currentMonth <= _minimumDate.month() && _currentYear <= _minimumDate.year() && _wheelCount == -1) {
            _wheelCount = 0;
            return;
        }
        if(_wheelCount <= -3) {
            _wheelCount = 1;
            _currentMonth--;
        }
        if(!isWheel) {
            _currentMonth--;
            _wheelCount = 0;
        }
        if(!validDate()) return;
        generateDayInMonth(_currentYear, _currentMonth, _wheelCount);
        break;
    case YEAR:
        if(QDate(_currentYear - 1, _currentMonth, _currentDay) < _minimumDate) return;
        _currentYear--;
        _title->setText(QString::number(_currentYear));
        break;
    case YEAR12:
        if(QDate(_currentYear - 9, _currentMonth, _currentDay) < _minimumDate) return;
        _currentYear -= 10;
        generateYearInDecade(_currentYear);
    default:
        break;
    }
}

void CalendarWidget::showCalendar(CalendarWidget::DateViewState state)
{
    _state = state;
    switch(state) {
    case MONTH:
        _frameMonth->show();
        _frameYear->hide();
        _frameDecade->hide();
        break;
    case YEAR:
        _frameYear->show();
        _frameMonth->hide();
        _frameDecade->hide();
        _title->setText(QString::number(_currentYear));
        break;
    case YEAR12:
    default:
        _frameYear->hide();
        _frameMonth->hide();
        _frameDecade->show();
        break;
    }
}

bool CalendarWidget::validDate()
{
    int m = _currentMonth, y = _currentYear;
    int testFlag = 0;
    if(_currentMonth > 12) {
        testFlag = 1;
        _currentMonth = 1;
        _currentYear++;
    }
    if(_currentMonth < 1) {
        testFlag = 2;
        _currentMonth = 12;
        _currentYear--;
    }
    if((QDate(_currentYear, _currentMonth, _currentDay) > _maximumDate) ||
            (QDate(_currentYear, _currentMonth, _currentDay) < _minimumDate)) {
        _currentYear = y;
        _currentMonth = (testFlag == 1) ? 12 : ((testFlag == 2) ? 1 : m);
        return false;
    }
    return true;
}

CalendarItem::CalendarItem(QWidget *parent) : QLabel(parent)
{
    setObjectName("DatePickerDayInMonth");
    setFocusPolicy(Qt::NoFocus);
    setCursor(Qt::ArrowCursor);
}

void CalendarItem::setYear(int number, bool isCurrent)
{
    this->_year = number;
    this->_state = YEAR;
    StyleSheetManager::changeObjectName(this, "DatePickerMonthYear");
    if(isCurrent) {
        StyleSheetManager::changeProperty(this, "State", "");
    }
    else {
        StyleSheetManager::changeProperty(this, "State", "Not_Current_Month");
    }
    this->setText(QString::number(number));
}

void CalendarItem::setDay(QDate date, bool isCurrent)
{
    this->_date = date;
    this->_state = DAY;
    if(isCurrent) {
        StyleSheetManager::changeProperty(this, "State", "");
        if(QDate::currentDate().daysTo(this->_date) == 0) {
            StyleSheetManager::changeProperty(this, "State", "Today");
        }
    }
    else {
        StyleSheetManager::changeProperty(this, "State", "Not_Current_Month");
    }
    this->setText(QString::number(date.day()));
}

void CalendarItem::setMonthStr(int month, bool isCurrent)
{
    this->_state = MONTH;
    this->_month = month;
    StyleSheetManager::changeObjectName(this, "DatePickerMonthYear");
    if(isCurrent) {
        StyleSheetManager::changeProperty(this, "State", "");
    }
    else {
        StyleSheetManager::changeProperty(this, "State", "Not_Current_Month");
    }
    QString monthStr;
    QLocale _locale = QLocale(QLocale::Vietnamese, QLocale::Vietnam);
    monthStr = _locale.toString(QDate(1900, month, 1), "MMMM");
    monthStr = monthStr.left(1).toUpper() + monthStr.mid(1);
    this->setContentsMargins(4, 0, 4, 0);
    this->setText(monthStr);
    this->setWordWrap(true);
}

void CalendarItem::setEnabled(bool enable)
{
    this->_enable = enable;
    if(enable) {
        setCursor(Qt::ArrowCursor);
    }
    else {
        setCursor(Qt::ForbiddenCursor);
    }
}

void CalendarItem::mousePressEvent(QMouseEvent *event)
{
    (void)event;
    if(!_enable)  return;
    switch(_state) {
    case DAY:
        emit clicked(_date);
        break;
    case MONTH:
        emit clicked(_month);
        break;
    case YEAR:
        emit clicked(_year);
        break;
    }
}
