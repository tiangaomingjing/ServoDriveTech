#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T17:06:00
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TEMPLATE = lib

APP_BUILD_PATH=$${PWD}/../../../build/
MYLIB_PATH=$${PWD}/../../
INCLUDEPATH +=$${MYLIB_PATH}/UI/IUiWidget\
              $${MYLIB_PATH}/UI/UiPlot\
              $${MYLIB_PATH}/Option\
              $${MYLIB_PATH}/GTUtils\
              $${MYLIB_PATH}/SDKernel\
              $${PWD}/../../../Common/src/SdtGlobal\
              $${PWD}/../IPlotUnit

CONFIG(debug, debug|release){

    PLOT_OUT_PATH=$${APP_BUILD_PATH}/debug/bin
    LIBS +=$${PLOT_OUT_PATH}/UiPlotd.lib\
           $${PLOT_OUT_PATH}/IUiWidgetd.lib\
           $${PLOT_OUT_PATH}/GTUtilsd.lib\
           $${PLOT_OUT_PATH}/Optiond.lib\
           $${PLOT_OUT_PATH}/SDKerneld.lib\
           $${PLOT_OUT_PATH}/IPlotUnitd.lib

    TARGET = PlotUnitGraphd
} else{
    PLOT_OUT_PATH=$${APP_BUILD_PATH}/release/bin
    LIBS +=$${PLOT_OUT_PATH}/UiPlot.lib\
           $${PLOT_OUT_PATH}/IUiWidget.lib\
           $${PLOT_OUT_PATH}/GTUtils.lib\
           $${PLOT_OUT_PATH}/Option.lib\
           $${PLOT_OUT_PATH}/SDKernel.lib\
           $${PLOT_OUT_PATH}/IPlotUnit.lib

    TARGET = PlotUnitGraph
}
DESTDIR =$${PLOT_OUT_PATH}

DEFINES += PLOTUNITGRAPH_LIBRARY

SOURCES += \
    plotunitgraph129.cpp \
    iplotunitgraph.cpp

HEADERS += \
        plotunitgraph_global.h \
    plotunitgraph129.h \
    iplotunitgraph.h \
    iplotunitgraph_p.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    plotunitgraph129.ui

TRANSLATIONS    += ch_plotunit.ts en_plotunit.ts
