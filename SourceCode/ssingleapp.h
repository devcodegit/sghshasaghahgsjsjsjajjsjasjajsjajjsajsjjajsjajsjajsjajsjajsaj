#ifndef SSINGLEAPP_H
#define SSINGLEAPP_H

#include <QApplication>

class SSingleApp : public QApplication
{
    Q_OBJECT
public:
    explicit SSingleApp(int &argc, char *argv[]);

    void checkSingleInstance();
    void startApplication();

signals:

public slots:
};

#endif // SSINGLEAPP_H
