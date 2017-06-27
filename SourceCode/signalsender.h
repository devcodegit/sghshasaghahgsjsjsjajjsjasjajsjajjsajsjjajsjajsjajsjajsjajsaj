#ifndef SIGNALSENDER_H
#define SIGNALSENDER_H
#include <QObject>
class SignalSender : public QObject
{
    Q_OBJECT
    static SignalSender *Instance;
    explicit SignalSender() {}
public:
    static SignalSender *instance() {
        if(!Instance) {
            Instance = new SignalSender;
        }
        return Instance;
    }
signals:
    void homeClicked();
    void managementClicked();
    void settingClicked();
    void showMoreInfo(int moreId);
};


#endif // SIGNALSENDER_H
