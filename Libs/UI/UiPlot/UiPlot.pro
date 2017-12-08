#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:57:15
#
#-------------------------------------------------
include (../UI.pri)

QT       += widgets

QT       -= gui

TEMPLATE = lib

DEFINES += UIPLOT_LIBRARY

CONFIG(debug, debug|release){
    TARGET = UiPlotd
} else{
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
