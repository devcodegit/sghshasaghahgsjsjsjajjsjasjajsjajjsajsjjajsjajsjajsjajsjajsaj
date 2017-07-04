#ifndef PAGESEARCH_H
#define PAGESEARCH_H

#include <QWidget>
#include <QTimer>
#include "../object_listenter.h"
//#include "../lazada/lazada_handler.h"

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

namespace Lazada { namespace DataModel {
    class DataOrderItem;
    class DataOrder;
}}
using namespace Lazada::DataModel;
using namespace Core::Listener;

class PageSearch : public QWidget, public ObjectListenter
{
    Q_OBJECT
public:
    explicit PageSearch(QWidget *parent = 0);


    virtual void OnRequestCompleted(ResultListener *result);
    virtual void OnRequestFailed(ResultListener *result);
protected:
    virtual bool eventFilter(QObject *object, QEvent *event);
    virtual void showEvent(QShowEvent *);

signals:

public slots:

private slots:
    void onSearch();
    void onJumping(int page);
    void onShowInfo(int row, int col);
    void onCheckUpdateData();

private:
    QFrame *resultFrame = 0;
    QLineEdit *line1 = 0, *line2 = 0, *line3 = 0;
    QPushButton *searchButton = 0;
    QStandardItemModel *model = 0;
    STableView *tableView = 0;
    PageNavigation *pageNavigation = 0;
    SFilterInfo *filterInfo = 0;
    DetailWidget *infoDialog  = 0;
//    STableView *qmlTableView = 0;
    QStringList linesList;
    QStringList header;
//    QList<LazadaDataItemOrder*> listItem;
    QList<DataOrder *> listItem;
    int currentPage = 0;
    bool needUpdate = false;
    QTimer checkUpdateTimer;
    DateRangeWidget *dateRange = 0;

private:
    void readData(); //for testing
    void preloadData();
};

#endif // PAGESEARCH_H
