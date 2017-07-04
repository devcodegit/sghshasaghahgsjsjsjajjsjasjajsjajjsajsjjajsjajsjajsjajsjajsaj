#ifndef PRINT_MANAGER_H
#define PRINT_MANAGER_H

#include <QMutex>
#include <QtPrintSupport/QPrintDialog>

class PrintManager
{
    PrintManager();
    static PrintManager *Instance;
    static QMutex mutexIns;
public:
    static PrintManager *instance();

    void print();
    void setFile(const QString &pathFile);

private:
    QPrintDialog *_pPrintDialog;

    QString _strPathFile;
};

#endif // PRINT_MANAGER_H
