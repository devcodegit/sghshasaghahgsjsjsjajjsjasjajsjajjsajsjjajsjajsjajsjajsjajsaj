#ifndef PAGENAVIGATION_H
#define PAGENAVIGATION_H

#include <QLabel>
#include <QWidget>
#include <QMap>

class QHBoxLayout;
class QPushButton;

class PageItem : public QLabel
{
    Q_OBJECT
public:
    enum Type {
        Page,
        NextNavigation,
        PreviousNavigation,
        FirstPageNavigation,
        LastPageNavigation
    };

    explicit PageItem(Type type = Page, QWidget *parent = 0);
    void setId(int id);
    int getId();
    void setHighlight();
    void clearHighlight();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void clicked(int id);
    void clicked();
private:
    int id;
    Type type;
};

class PageNavigation : public QWidget
{
    Q_OBJECT
public:
    explicit PageNavigation(QWidget *parent = 0);
    void setCurrentPage(int page);
    void setRange(int from, int to, int range = -1);

signals:

public slots:
private slots:
    void onDirectingToPage(int page);
    void onNext();
    void onPrev();
    void onFirstPage();
    void onLastPage();

private:
    QList<PageItem*> listItem;
    QMap<int, PageItem*> mapItem;
    QHBoxLayout *mainLayout = 0;
    PageItem *currentItem = 0;
    PageItem *next, *prev, *first, *last;
    int currentPage;
    int maxViewRange = 4;
    int tempFrom, tempTo;
    int from, to;

private:
    void moveRange(int from, int to);

};

#endif // PAGENAVIGATION_H
