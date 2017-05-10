#ifndef STYLESHEETMANAGER_H
#define STYLESHEETMANAGER_H

#include <QList>

class QApplication;
class QMutex;
class QString;
class QVariant;
class QWidget;

class StyleSheetManager
{

private:
    static StyleSheetManager *Instance;
    static QMutex _mutexIns;
    static const QString STYLE_FILE_NAME_FORMAT;
    static const int SCALE_FACTOR_1 = 100;
    static const int DEFAULT_SCALE_FACTOR = SCALE_FACTOR_1;
    static const QList<int> SUPPORTED_SCALE_FACTORS;

    explicit StyleSheetManager();

public:
    // instance
    static StyleSheetManager *instance();
    static void changeObjectName(QWidget *widget, const QString &newObjectName);
    static void changeProperty(QWidget *widget,
                               const QString &propertyName,
                               const QVariant &value,
                               bool updateByParent = false);

    void loadStyleSheetToApp(QApplication &app);

};

#endif // STYLESHEETMANAGER_H
