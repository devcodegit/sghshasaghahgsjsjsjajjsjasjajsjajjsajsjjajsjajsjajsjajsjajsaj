#ifndef PAGESEARCH_H
#define PAGESEARCH_H

#include <QWidget>

class QScrollArea;
class QLineEdit;
class QPushButton;
class QFrame;
class QStandardItemModel;
class STableView;
class PageNavigation;
class SFilterInfo;
//class STableView;

class PageSearch : public QWidget
{
    Q_OBJECT
public:
    explicit PageSearch(QWidget *parent = 0);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);

signals:

public slots:

private slots:
    void onSearch();
    void onJumping(int page);

private:
    QFrame *resultFrame = 0;
    QLineEdit *line1 = 0, *line2 = 0, *line3 = 0, *line4 = 0;
    QPushButton *searchButton = 0;
    QStandardItemModel *model = 0;
    STableView *tableView = 0;
    PageNavigation *pageNavigation = 0;
    SFilterInfo *filterInfo = 0;
//    STableView *qmlTableView = 0;
    QStringList testList;
    QStringList header;

private:
    void readData(); //for testing
};

#endif // PAGESEARCH_H
