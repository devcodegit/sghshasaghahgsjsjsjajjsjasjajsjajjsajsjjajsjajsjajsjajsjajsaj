#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include <QFrame>
#include <QStringList>
#include <QList>
#include "CustomControl/drop-down-widget.h"

class QVBoxLayout;
class QFrame;
class QScrollArea;
class VerticalScrollbar;
class DropdownWidget;

class NavigationBar : public QFrame
{
    Q_OBJECT
    explicit NavigationBar(QWidget *parent = 0);
    static NavigationBar *Instance;
public:
    static NavigationBar* instance() {
        if(!Instance) {
            Instance = new NavigationBar;
        }
        return Instance;
    }

    void addContent(const QString &title, QList<DropdownWidget::ContentAction *> contents);

protected:
    virtual void resizeEvent(QResizeEvent *event);

signals:

public slots:

private slots:
    void onItemDropDown();
    void onScrollValueChanged(int value);

private:
    QVBoxLayout *contentLayout = 0;
    QFrame *contentFrame = 0;
    QList<QWidget*> listItems;
    QScrollArea *scrollArea;
    VerticalScrollbar *scrollBar;
    QWidget *scroll;
};

#endif // NAVIGATIONBAR_H
