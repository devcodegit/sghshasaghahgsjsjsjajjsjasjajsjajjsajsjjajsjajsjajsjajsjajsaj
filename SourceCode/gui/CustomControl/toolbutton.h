#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QFrame>

class QMenu;
class QAction;
class QLabel;
class SvgWidget;

class ToolButton : public QFrame
{
    Q_OBJECT
public:
    explicit ToolButton(QWidget *parent = 0);
    void setMenu(QMenu *menu);
    void setDefaultAction(QAction *action);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);

signals:

public slots:

private slots:
    void onShowMenu();
    void onTriggerDefaultAction();

private:
    QWidget  *menuOn = 0;
    QMenu *menu = 0;
    QAction *defaultAction = 0;
    QFrame *titleFrame = 0;
    QLabel *title = 0;
    QFrame *arrowFrame = 0;
    SvgWidget *arrowIcon = 0;

};

#endif // TOOLBUTTON_H
