#ifndef SFILTERINFO_H
#define SFILTERINFO_H

#include <QFrame>
#include <QList>
#include <QMap>

class QSvgWidget;
class QLabel;
class FlowLayout;
class QScrollArea;
class VerticalScrollbar;

class FilterItem : public QFrame
{
    Q_OBJECT
public:
    enum FilterItemState {
        USING,
        NotUSING
    };

    explicit FilterItem(QWidget *parent = 0);
    void setTitle(const QString &title);
    QString getTitle();
    FilterItemState state() { return _state;}
protected:

    virtual bool eventFilter(QObject *object, QEvent *event);

signals:
    void closeItem();

private:
    QLabel *_title;
    QSvgWidget * _closeWg;
    FilterItemState _state = NotUSING;

};

class SFilterInfo : public QWidget
{
    Q_OBJECT
public:
    enum {
        ID_NUM_BILL = 0,
        ID_NAME_CUSTOMER,
        ID_NAME_PRODUCT,
        ID_START_DATE,
        ID_END_DATE
    };
    explicit SFilterInfo(QWidget *parent = 0);
    void addItem(const QString &title, int id);
    QStringList getFilterList();

protected:
    virtual void resizeEvent(QResizeEvent *event);

signals:

public slots:

private slots:
    void onRemoveItem();
    void onScrollValueChanged(int value);

private:
    QMap<int, FilterItem*> mapItems;
    FlowLayout *filterItemLayout;
    QWidget *scroll;
    QScrollArea *scrollArea;
    VerticalScrollbar *scrollBar;

private:
    FilterItem *getItem(int id, bool &isNew);
};

#endif // SFILTERINFO_H
