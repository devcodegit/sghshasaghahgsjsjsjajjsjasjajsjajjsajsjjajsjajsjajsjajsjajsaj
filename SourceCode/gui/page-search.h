#ifndef PAGESEARCH_H
#define PAGESEARCH_H

#include <QWidget>

class QScrollArea;
class QLineEdit;
class QPushButton;
class QFrame;

class PageSearch : public QWidget
{
    Q_OBJECT
public:
    explicit PageSearch(QWidget *parent = 0);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);
signals:

public slots:

private:
    QFrame *resultFrame = 0, *contentResult = 0;
    QScrollArea *resultArea = 0;
    QLineEdit *searchLineEdit = 0;
    QPushButton *searchButton = 0;
};

#endif // PAGESEARCH_H
