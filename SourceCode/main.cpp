#include "gui/smainwindow.h"
#include "ssingleapp.h"

int main(int argc, char *argv[])
{
    SSingleApp app(argc, argv);

    SMainWindow window;
    window.show();

    return app.exec();
}
