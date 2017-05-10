#include "style-sheet-manager.h"

#include <QMutex>
#include <QApplication>
#include <QWidget>
#include <QStyle>
#include <QDebug>

StyleSheetManager *StyleSheetManager::Instance = NULL;
QMutex StyleSheetManager::_mutexIns;
const QString StyleSheetManager::STYLE_FILE_NAME_FORMAT = ":/Style/Style/x%1/style.css";
const QList<int> StyleSheetManager::SUPPORTED_SCALE_FACTORS = QList<int>() << SCALE_FACTOR_1;

StyleSheetManager *StyleSheetManager::instance()
{
    if (!Instance)
    {
        _mutexIns.lock();
        if (!Instance)
        {
            Instance = new StyleSheetManager();
        }
        _mutexIns.unlock();
    }
    return Instance;
}

StyleSheetManager::StyleSheetManager()
{

}

void StyleSheetManager::changeObjectName(QWidget *widget, const QString &newObjectName)
{
    if (widget == NULL)
        return;

    widget->setObjectName(newObjectName);
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
}

void StyleSheetManager::changeProperty(QWidget *widget, const QString &propertyName, const QVariant &value, bool updateByParent)
{
    if (widget == NULL)
        return;

    widget->setProperty(propertyName.toStdString().c_str(), value);

    QWidget *updateWidget = updateByParent ? widget->parentWidget() : widget;
    if (updateWidget == NULL)
        return;

    updateWidget->style()->unpolish(widget);
    updateWidget->style()->polish(widget);
}

void StyleSheetManager::loadStyleSheetToApp(QApplication &app)
{
    // Todo: get screen's scale factor
    int scale = 100;

    if (!SUPPORTED_SCALE_FACTORS.contains(scale))
    {
        qDebug() << "Unsupported scale factor: " << scale;
        scale = DEFAULT_SCALE_FACTOR;
    }

    QString resName = STYLE_FILE_NAME_FORMAT.arg(QString::number(scale));
    qDebug() << "Current screen's scale factor: " <<  scale;
    qDebug() << "Load style sheet file: {}" << resName;

    QFile styleFile(resName);
    if (styleFile.open(QFile::ReadOnly))
    {
        QString styleSheet = styleFile.readAll();
        app.setStyleSheet(styleSheet);
        styleFile.close();
    }
    else
    {
        qDebug() << "Load style sheet failed";
    }
}
