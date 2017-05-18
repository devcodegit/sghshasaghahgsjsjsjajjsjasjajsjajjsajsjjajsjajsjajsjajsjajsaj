QT += core gui widgets svg
TARGET = SaleApp
TEMPLATE = app
CONFIG -= console

SOURCES += \
    SourceCode/main.cpp \
    SourceCode/gui/CustomControl/swidget.cpp \
    SourceCode/gui/smainwindow.cpp \
    SourceCode/ssingleapp.cpp \
    SourceCode/style-sheet-manager.cpp \
    SourceCode/gui/CustomControl/sbuttonoption.cpp \
    SourceCode/gui/CustomControl/stabwidget.cpp \
    SourceCode/gui/page-search.cpp \
    SourceCode/gui/CustomControl/sconstantmenu.cpp \
    SourceCode/gui/CustomControl/page-navigation.cpp \
    SourceCode/gui/CustomControl/testingcellui.cpp \
    SourceCode/gui/CustomControl/cache.cpp \
    SourceCode/gui/CustomControl/sitemdelegate.cpp \
    SourceCode/gui/CustomControl/stableview.cpp \
    SourceCode/gui/CustomControl/sfilter-info.cpp \
    SourceCode/gui/CustomControl/flowlayout.cpp \
    SourceCode/gui/CustomControl/verticalscrollbar.cpp
HEADERS += \
    SourceCode/gui/CustomControl/swidget.h \
    SourceCode/gui/smainwindow.h \
    SourceCode/ssingleapp.h \
    SourceCode/style-sheet-manager.h \
    SourceCode/uiconst.h \
    SourceCode/gui/CustomControl/sbuttonoption.h \
    SourceCode/gui/CustomControl/stabwidget.h \
    SourceCode/gui/page-search.h \
    SourceCode/gui/CustomControl/sconstantmenu.h \
    SourceCode/gui/CustomControl/page-navigation.h \
    SourceCode/gui/CustomControl/testingcellui.h \
    SourceCode/gui/CustomControl/sitemdelegate.h \
    SourceCode/gui/CustomControl/cache.h \
    SourceCode/gui/CustomControl/stableview.h \
    SourceCode/gui/CustomControl/sfilter-info.h \
    SourceCode/gui/CustomControl/flowlayout.h \
    SourceCode/gui/CustomControl/verticalscrollbar.h

RESOURCES += \
    Resource/resource.qrc

DISTFILES += \
    Resource/Style/Generic/style.scss \
    Resource/Style/x100/style.scss


#kha test
