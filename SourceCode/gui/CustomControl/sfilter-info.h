#ifndef SFILTERINFO_H
#define SFILTERINFO_H

#include <QWidget>
#include <QList>

class QSvgWidget;
class QLabel;
class FlowLayout;
class QScrollArea;

class FilterItem : public QWidget
{
    Q_OBJECT
public:
    enum FilterItemState {
        USING,
        NotUSING
    };

    explicit FilterItem(QWidget *parent = 0);
    void setTitle(const QString &title);
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
    explicit SFilterInfo(QWidget *parent = 0);
    void addItem(const QString &title);

protected:
    virtual void resizeEvent(QResizeEvent *event);

signals:

public slots:

private slots:
    void onRemoveItem();

private:
    QList<FilterItem*> listItems;
    FlowLayout *filterItemLayout;
    QWidget *scroll;
    QScrollArea *scrollArea;

private:
    FilterItem *getItem();
};

#endif // SFILTERINFO_H
