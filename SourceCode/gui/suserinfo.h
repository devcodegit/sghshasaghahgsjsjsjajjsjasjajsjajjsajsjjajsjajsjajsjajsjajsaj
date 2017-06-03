#ifndef SUSERINFO_H
#define SUSERINFO_H

#include <QWidget>
#include "CustomControl/sdialog.h"

class SUserInfo : public SDialog
{
    Q_OBJECT
    explicit SUserInfo(QWidget *parent = 0);
    static SUserInfo *Instance;
public:
    static SUserInfo *instance() {
        if(!Instance) {
            Instance = new SUserInfo;
        }
        return Instance;
    }

    void setData();

signals:

public slots:
};

#endif // SUSERINFO_H
