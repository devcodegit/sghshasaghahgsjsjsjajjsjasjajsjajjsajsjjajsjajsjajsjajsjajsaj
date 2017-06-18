#include "date-range-widget.h"
#include <QBoxLayout>
#include <QLabel>
#include <QSvgWidget>
#include <QEvent>
#include <QDebug>

#define HEIGHT 50

DateRangeWidget::DateRangeWidget(QWidget *parent) : QFrame(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    dateStartLbl = new QLabel;
    dateStartLbl->setObjectName("DefaultLbl");
    dateStartLbl->installEventFilter(this);
    dateStartLbl->setAlignment(Qt::AlignCenter);
    dateStartLbl->setCursor(Qt::PointingHandCursor);
    dateEndLbl = new QLabel;
    dateEndLbl->setObjectName("DefaultLbl");
    dateEndLbl->installEventFilter(this);
    dateEndLbl->setAlignment(Qt::AlignCenter);
    dateEndLbl->setCursor(Qt::PointingHandCursor);
    QLabel *dash = new QLabel;
    dash->setText("-");
    dash->setAlignment(Qt::AlignCenter);
    QSvgWidget* dateIcon = new QSvgWidget;
    dateIcon->load(QString(":/Icon/Image/calendar.svg"));
    dateIcon->setFixedSize(20, 20);
    mainLayout->addWidget(dateStartLbl);
    mainLayout->addWidget(dash);
    mainLayout->addWidget(dateEndLbl);
    mainLayout->addWidget(dateIcon);
    reset();
}

void DateRangeWidget::setStartDate(QDate date)
{
    startDate = date;
}

void DateRangeWidget::setEndDate(QDate date)
{
    endDate = date;
}

void DateRangeWidget::reset()
{
    dateStartLbl->setText("Ngày bắt đầu");
    dateEndLbl->setText("Ngày kết thúc");
}

bool DateRangeWidget::eventFilter(QObject *object, QEvent *event)
{
    if(object == dateStartLbl) {
        if(event->type() == QEvent::MouseButtonRelease) {
            onStartClicked();
        }
    }
    else if(object == dateEndLbl) {
        if(event->type() == QEvent::MouseButtonRelease) {
            onEndClicked();
        }
    }
    return QFrame::eventFilter(object, event);
}

void DateRangeWidget::onStartClicked()
{
    qDebug () << "onStartClicked();";
}

void DateRangeWidget::onEndClicked()
{
    qDebug () << "onEndClicked();";
}
