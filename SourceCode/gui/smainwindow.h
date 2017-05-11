#ifndef SMAINWINDOW_H
#define SMAINWINDOW_H

#include "CustomControl/swidget.h"

class QFrame;
class QVBoxLayout;
class STabWidget;
class PageSearch;
class SConstantMenu;

class SMainWindow : public SWidget
{
    Q_OBJECT
public:
    explicit SMainWindow(QWidget *parent = 0);

signals:

public slots:

protected:
    virtual void resizeEvent(QResizeEvent *ev);

private:
    void createHeader();
    void createMidle();
    void updateSize();

private:
    QVBoxLayout *_pvLayout = 0;
    QFrame *_pHeader = 0;
    QFrame *_pMidle = 0;
    QFrame *_pMidleOption = 0;
    QFrame *_pMidleSearch = 0;
    QFrame *_pMidleResult = 0;
    STabWidget *tab = 0;
    PageSearch *pageSearch = 0;
    SConstantMenu *menu = 0;
};

#endif // SMAINWINDOW_H
