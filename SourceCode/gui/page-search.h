#ifndef PAGESEARCH_H
#define PAGESEARCH_H

#include <QWidget>
#include <QTimer>
#include <QFrame>
#include <QDate>
#include <QMap>
#include "../lazada/lazada_handler.h"

class QScrollArea;
class QLineEdit;
class QPushButton;
class QFrame;
class QStandardItemModel;
class STableView;
class PageNavigation;
class SFilterInfo;
//class STableView;
class DetailWidget;
class DateRangeWidget;

class DataHandler;
class TinyTableWidget;

class CalendarWidget;
class ToolButton;
class QAction;
class LoadingControl;
class QLabel;

using namespace Lazada::Controls;

class PageSearch : public QFrame, public IObjRequestListener
{
    Q_OBJECT
public:
    enum PAGE {
        ALL,
        PROCESSING,
        READY,
        TRANSMITTING,
        DONE
    };

    explicit PageSearch(QWidget *parent = 0);


    virtual void OnRequestCompleted(ResponseResult *result);
    virtual void OnRequestFailed(ResponseResult *result);

    void navigate(PAGE page);
protected:
    virtual bool eventFilter(QObject *object, QEvent *event);
    virtual void showEvent(QShowEvent *);
    virtual void resizeEvent(QResizeEvent *event);

signals:

public slots:

private slots:
    void onSearch();
    void onJumping(int page);
    void onShowInfo(int row, int col);
    void onUpdateCheckbox(int row, int col, bool val);
    void onCheckUpdateData();
    void onAddFilterItem(QDate date);
    void onShowCalendar(bool isStart, QDate date);
    void onReadyChangeState();
    void onCancelChangeState();
    void onExport();
    void onPrint();
    void onCsv();

private:
    QFrame *resultFrame = 0;
    QLineEdit *line1 = 0, *line2 = 0, *line3 = 0;
    QPushButton *searchButton = 0;
    QStandardItemModel *model = 0;
    QStandardItemModel *modelReady = 0;
    QStandardItemModel *modelTransmitting = 0;
    QStandardItemModel *modelProcessing = 0;
    QStandardItemModel *modelDone = 0;
    STableView *tableView = 0;
    PageNavigation *pageNavigation = 0;
    SFilterInfo *filterInfo = 0;
    DetailWidget *infoDialog  = 0;
//    STableView *qmlTableView = 0;
    QStringList linesList;
    QList<LazadaDataItemOrder*> listItem;
    QMap<int, LazadaDataItemOrder*> mapItems;
    int currentPage = 0;
    bool needUpdate = false;
    bool isStartClicked = true;
    QTimer checkUpdateTimer;
    DateRangeWidget *dateRange = 0;
    CalendarWidget *calendarWidget = 0;


    DataHandler *dataHandler = 0;
    TinyTableWidget *table = 0;

    ToolButton *btnChangeState = 0;
    QAction *actionReady  = 0;
    QAction *actionCancel = 0;

    ToolButton *btnExport = 0;
    QAction *actionCsvFileExport = 0;
    QAction *actionPrint = 0;

    LoadingControl *loading = 0;
    QLabel *errorLbl = 0;

private:
    void readData(); //for testing
    void preloadData();
    void pushReadyData();

    void allItems();
    void processingItems();
    void readyItems();
    void transmittingItems();
    void doneItems();
};

#endif // PAGESEARCH_H
