#ifndef STABWIDGET_H
#define STABWIDGET_H

#include <QWidget>
#include <QMap>

class QHBoxLayout;
class QFrame;
class QScrollArea;
class QLabel;

class STabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit STabWidget(QWidget *parent = 0);
    void addItem(const QString &title, QWidget *contentWg);

signals:

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual bool eventFilter(QObject *object, QEvent *event);
    virtual void showEvent(QShowEvent*);

public slots:

private slots:
    void onScroll(int value);


private:
    QHBoxLayout *tabLayout = 0;
    QFrame *tabFrame = 0, *tab = 0;
    QFrame *contentFrame = 0;
    QMap<QFrame*, QWidget*> mapTabContent;
    QScrollArea *tabScrollArea = 0;
    QWidget *currentContent = 0;

private:
    void showTab(QFrame *tab);
};

#endif // STABWIDGET_H
