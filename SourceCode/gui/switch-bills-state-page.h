#ifndef SWITCHBILLSSTATEPAGE_H
#define SWITCHBILLSSTATEPAGE_H

#include <QFrame>

class QLabel;
class QPushButton;

class SwitchBillsStatePage : public QFrame
{
    Q_OBJECT
public:
    enum {
        INIT = 0,
        PREVIEW = 1,
        READY = 2
    };

    explicit SwitchBillsStatePage(QWidget *parent = 0);
    void setState(int state);
    void nextState();

private slots:
    void onSave();
    void onChange();
    void onAllDocs();
    void onBills();
    void onStamp();

private:
    int currentState = INIT;
    QLabel *title = 0;
    QPushButton *btnChange, *btnClose, *btnSave, *btnAll, *btnBill, *btnStamp;
private:
    void uiStateInit();
    void uiStatePreview();
    void uiStateReady();

};

#endif // SWITCHBILLSSTATEPAGE_H
