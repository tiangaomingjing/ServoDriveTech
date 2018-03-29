#-------------------------------------------------
#
# Project created by QtCreator 2017-12-11T20:23:12
#
#-------------------------------------------------
include(../Libs.pri)

INCLUDEPATH +=$${PWD}/../UI/IUiWidget\
              $${PWD}/../UI/UiPlot

QT       += widgets

QT       -= gui

TEMPLATE = lib
CONFIG(debug, debug|release){

    PLOT_OUT_PATH=$${APP_BUILD_PATH}/debug/bin
    LIBS +=$${PLOT_OUT_PATH}/UiPlotd.lib\
           $${PLOT_OUT_PATH}/IUiWidgetd.lib\
           $${PLOT_OUT_PATH}/GTUtilsd.lib\
           $${PLOT_OUT_PATH}/Optiond.lib\
           $${PLOT_OUT_PATH}/SDKerneld.lib

    TARGET = PlotUnitd
} else{
    PLOT_OUT_PATH=$${APP_BUILD_PATH}/release/bin
    LIBS +=$${PLOT_OUT_PATH}/UiPlot.lib\
           $${PLOT_OUT_PATH}/IUiWidget.lib\
           $${PLOT_OUT_PATH}/GTUtils.lib\
           $${PLOT_OUT_PATH}/Option.lib\
           $${PLOT_OUT_PATH}/SDKernel.lib

    TARGET = PlotUnit
}
DESTDIR =$${PLOT_OUT_PATH}

DEFINES += PLOTUNIT_LIBRARY

SOURCES += plotunit.cpp \
    iplotunit.cpp \
    plotunit129.cpp

HEADERS += plotunit.h\
        plotunit_global.h \
    iplotunit.h \
    iplotunit_p.h \
    plotunit129.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    plotunit.ui \
    plotunit129.ui

TRANSLATIONS    += ch_plotunit.ts en_plotunit.ts
