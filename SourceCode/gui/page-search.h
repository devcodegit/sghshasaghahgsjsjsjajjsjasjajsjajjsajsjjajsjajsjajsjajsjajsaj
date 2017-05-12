#ifndef PAGESEARCH_H
#define PAGESEARCH_H

#include <QWidget>

class QScrollArea;
class QLineEdit;
class QPushButton;
class QFrame;
class QStandardItemModel;
class QTableView;

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

private:
    QFrame *resultFrame = 0;
    QLineEdit *searchLineEdit = 0;
    QPushButton *searchButton = 0;
    QStandardItemModel *model = 0;
    QTableView *tableView = 0;

private:
    void readData(); //for testing
};

#endif // PAGESEARCH_H
