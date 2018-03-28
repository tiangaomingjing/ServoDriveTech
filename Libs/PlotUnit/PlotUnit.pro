#-------------------------------------------------
#
# Project created by QtCreator 2017-12-11T20:23:12
#
#-------------------------------------------------
include(../Libs.pri)

QT       += widgets

QT       -= gui

TEMPLATE = lib
CONFIG(debug, debug|release){
    LIBS +=
    PLOT_OUT_PATH=$${APP_BUILD_PATH}/debug/bin
    TARGET = PlotUnitd
} else{
    LIBS +=
    PLOT_OUT_PATH=$${APP_BUILD_PATH}/release/bin
    TARGET = PlotUnit
}
DESTDIR =$${PLOT_OUT_PATH}

DEFINES += PLOTUNIT_LIBRARY

SOURCES += plotunit.cpp \
    iplotunit.cpp

HEADERS += plotunit.h\
        plotunit_global.h \
    iplotunit.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    plotunit.ui

TRANSLATIONS    += ch_plotunit.ts en_plotunit.ts
