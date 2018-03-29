#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:57:15
#
#-------------------------------------------------
include (../UI.pri)
INCLUDEPATH +=$${PWD}/../../PlotUnit/IPlotUnit

QT       += widgets

QT       -= gui

TEMPLATE = lib

DEFINES += UIPLOT_LIBRARY

CONFIG(debug, debug|release){
    LIBS +=$${APP_BUILD_PATH}/debug/bin/IPlotUnitd.lib
    TARGET = UiPlotd
} else{
    LIBS +=$${APP_BUILD_PATH}/release/bin/IPlotUnit.lib
    TARGET = UiPlot
}

SOURCES += uiplot.cpp

HEADERS += uiplot.h\
        uiplot_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uiplot.ui

#message("build path"+$${APP_BUILD_PATH})
