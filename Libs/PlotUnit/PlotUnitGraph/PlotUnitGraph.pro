#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T17:06:00
#
#-------------------------------------------------
include(../../PlotCurvePluginFramework/ctkplugins.pri)
QT       += widgets printsupport

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
              $${PWD}/../IPlotUnit\
              $${PWD}/../../PlotCurvePluginFramework/ICurve\
              $${PWD}/../../PlotCurvePluginFramework/PluginsManager\
              $${PWD}/DialogPickCurve\
              $${PWD}/CurveManager


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
    iplotunitgraph.cpp \
    gtplot.cpp \
    modectlpanel.cpp \
    qcpitemhandletag.cpp \
    qcpitemmeasure.cpp \
    qcustomplot.cpp \
    tabctlpanel129.cpp \
    ../../PlotCurvePluginFramework/PluginsManager/pluginsmanager.cpp \
    DialogPickCurve/dialogpickcurve.cpp \
    CurveManager/curvemanager.cpp \
    CurveManager/curvetableaxisitem.cpp

HEADERS += \
        plotunitgraph_global.h \
    plotunitgraph129.h \
    iplotunitgraph.h \
    iplotunitgraph_p.h \
    gtplot.h \
    modectlpanel.h \
    qcpitemhandletag.h \
    qcpitemmeasure.h \
    qcustomplot.h \
    tabctlpanel129.h \
    plottabctlprms.h \
    ../../PlotCurvePluginFramework/PluginsManager/pluginsmanager.h \
    DialogPickCurve/dialogpickcurve.h \
    CurveManager/curvemanager.h \
    CurveManager/curvetableaxisitem.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    plotunitgraph129.ui\
    tabctlpanel129.ui \
    DialogPickCurve/dialogpickcurve.ui

TRANSLATIONS    += ch_plotunit.ts en_plotunit.ts
