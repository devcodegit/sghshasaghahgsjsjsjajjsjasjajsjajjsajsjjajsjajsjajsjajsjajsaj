#ifndef QMLINTERFACE_H
#define QMLINTERFACE_H

#include <QObject>

class QMLInterface : public QObject
{
    Q_OBJECT
    static QMLInterface *Instance;
    QMLInterface();
public:
    static QMLInterface *instance() {
        if(!Instance) {
            Instance = new QMLInterface;
        }
        return Instance;
    }

    void setData();

signals:
    void setModelData();

public slots:
};

#endif // QMLINTERFACE_H
