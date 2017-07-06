#ifndef SMAINWINDOW_H
#define SMAINWINDOW_H

#include "CustomControl/swidget.h"

class QFrame;
class QVBoxLayout;
class STabWidget;
class PageSearch;
class SConstantMenu;
class QLabel;

class SMainWindow : public SWidget
{
    Q_OBJECT
public:
    explicit SMainWindow(QWidget *parent = 0);

signals:

public slots:

private slots:
    void onManagementClicked();
    void onLinkActivated(QString link);

protected:
    virtual void resizeEvent(QResizeEvent *ev);
    virtual bool eventFilter(QObject *object, QEvent *event);

private:
    void createHeader();
    void createMidle();
    void createNavigation();
    void updateSize();

private:
    QVBoxLayout *_pvLayout = 0;
    QFrame *headerArea = 0;
    QFrame *_pMidle = 0;
    QFrame *navigationArea = 0;
    QFrame *_pMidleSearch = 0;
    QFrame *contentArea = 0;
    STabWidget *managementPage = 0;
    PageSearch *pageSearch = 0;
    SConstantMenu *menu = 0;
    QLabel *avatar = 0;
    QLabel *info = 0;
};

#endif // SMAINWINDOW_H
