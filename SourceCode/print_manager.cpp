#include "print_manager.h"
#include <QtPrintSupport/QPrinter>
#include <QPrintPreviewDialog>
#include <QFile>
#include <QTextStream>
#include <QTextDocument>

QMutex PrintManager::mutexIns;
PrintManager *PrintManager::Instance = NULL;
PrintManager *PrintManager::instance()
{
    if (!Instance)
    {
        mutexIns.lock();
        if (!Instance)
        {
            Instance = new PrintManager();
        }
        mutexIns.unlock();
    }
    return Instance;
}

void PrintManager::print()
{
    if (_strPathFile.isEmpty()) return;
    QFile file(_strPathFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString htmlContent;
    QTextStream in(&file);
    in >> htmlContent;

    QTextDocument *document = new QTextDocument();
    document->setHtml(htmlContent);

    QPrinter printer;

//    QPrintDialog *dialog = new QPrintDialog(&printer);
//    if (dialog->exec() != QDialog::Accepted)
//        return;

    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(&printer);
//    dialog->open();
    dialog->exec();

//    document->print(&printer);

    delete document;
}

void PrintManager::setFile(const QString &pathFile)
{
    _strPathFile = pathFile;
}

PrintManager::PrintManager()
{
//    QPrinter printer;
//    _pPrintDialog = new QPrintDialog(&printer);
}

