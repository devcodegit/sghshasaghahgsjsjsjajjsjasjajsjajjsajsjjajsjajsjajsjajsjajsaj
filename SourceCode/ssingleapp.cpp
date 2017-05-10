#include "ssingleapp.h"
#include "SourceCode/style-sheet-manager.h"

SSingleApp::SSingleApp(int &argc, char *argv[]) : QApplication(argc, argv)
{
    checkSingleInstance();
}

void SSingleApp::checkSingleInstance()
{
    if (false)
    {
        // Todo: check app isRunning. Note: edit if...
    }
    else
    {
        startApplication();
    }
}

void SSingleApp::startApplication()
{
    StyleSheetManager::instance()->loadStyleSheetToApp(*this);
}
