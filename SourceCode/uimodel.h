#ifndef UIMODEL_H
#define UIMODEL_H
#include <QWidget>

class UIModel
{
    static UIModel *Instance;
    UIModel();
public:
    static UIModel *instance() {
        if(!Instance) {
            Instance = new UIModel;
        }
        return Instance;
    }
    void setMainWindow(QWidget *widget);
    QWidget *getMainWindow();

private:
    QWidget *mainWindow = 0;
};

#endif // UIMODEL_H
