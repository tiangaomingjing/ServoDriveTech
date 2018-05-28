#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T17:06:00
#
#-------------------------------------------------
include(../../PlotCurvePluginFramework/ctkplugins.pri)
include(../../SDMotion/MotionLibs.pri)
QT       += widgets printsupport
QT       -= gui

TEMPLATE = lib

APP_BUILD_PATH=$${PWD}/../../../build/
MYLIB_PATH=$${PWD}/../../
INCLUDEPATH +=$${MYLIB_PATH}/UI/IUiWidget\
              $${MYLIB_PATH}/UI/UiPlot\
              $${MYLIB_PATH}/Option\
              $${MYLIB_PATH}/GTUtils\
              $${MYLIB_PATH}/GTUtils/CmdManager\
              $${MYLIB_PATH}/GTUtils/QtTreeManager\
              $${MYLIB_PATH}/SDKernel\
              $${PWD}/../../../Common/src/SdtGlobal\
              $${PWD}/../IPlotUnit\
              $${PWD}/../../Com/Communication\
              $${PWD}/../../PlotCurvePluginFramework/ICurve\
              $${PWD}/../../PlotCurvePluginFramework/PluginsManager\
              $${PWD}/DialogPickCurve\
              $${PWD}/CurveManager\
              $${PWD}/Thread\
              $${PWD}/../../Com/Communication

CONFIG(debug, debug|release){

    PLOT_OUT_PATH=$${APP_BUILD_PATH}/debug/bin
    LIBS +=$${PLOT_OUT_PATH}/UiPlotd.lib\
           $${PLOT_OUT_PATH}/IUiWidgetd.lib\
           $${PLOT_OUT_PATH}/GTUtilsd.lib\
           $${PLOT_OUT_PATH}/Optiond.lib\
           $${PLOT_OUT_PATH}/SDKerneld.lib\
           $${PLOT_OUT_PATH}/IPlotUnitd.lib\
           $${PLOT_OUT_PATH}/MotionVelocityd.lib

    TARGET = PlotUnitGraphd
} else{
    PLOT_OUT_PATH=$${APP_BUILD_PATH}/release/bin
    LIBS +=$${PLOT_OUT_PATH}/UiPlot.lib\
           $${PLOT_OUT_PATH}/IUiWidget.lib\
           $${PLOT_OUT_PATH}/GTUtils.lib\
           $${PLOT_OUT_PATH}/Option.lib\
           $${PLOT_OUT_PATH}/SDKernel.lib\
           $${PLOT_OUT_PATH}/IPlotUnit.lib\
           $${PLOT_OUT_PATH}/MotionVelocity.lib

    TARGET = PlotUnitGraph
}
LIBS += -lOpenGL32

DESTDIR =$${PLOT_OUT_PATH}

DEFINES += PLOTUNITGRAPH_LIBRARY

SOURCES += \
    plotunitgraph129.cpp \
    iplotunitgraph.cpp \
    gtplot.cpp \
    qcpitemhandletag.cpp \
    qcpitemmeasure.cpp \
    qcustomplot.cpp \
    tabctlpanel129.cpp \
    ../../PlotCurvePluginFramework/PluginsManager/pluginsmanager.cpp \
    DialogPickCurve/dialogpickcurve.cpp \
    CurveManager/curvemanager.cpp \
    CurveManager/curvetableaxisitem.cpp \
    Thread/threadsample.cpp \
    Thread/threadcalculate.cpp \
    TabModeCtl/tabmodectl.cpp \
    TabMotion/tabmotion.cpp \
    itabwidget.cpp \
    TabModeCtl/modectlpanel.cpp

HEADERS += \
        plotunitgraph_global.h \
    plotunitgraph129.h \
    iplotunitgraph.h \
    iplotunitgraph_p.h \
    gtplot.h \
    qcpitemhandletag.h \
    qcpitemmeasure.h \
    qcustomplot.h \
    tabctlpanel129.h \
    plottabctlprms.h \
    ../../PlotCurvePluginFramework/PluginsManager/pluginsmanager.h \
    DialogPickCurve/dialogpickcurve.h \
    CurveManager/curvemanager.h \
    CurveManager/curvetableaxisitem.h \
    Thread/threadsample.h \
    Thread/threadcalculate.h \
    Thread/sampledata.h \
    plotdata.h \
    TabModeCtl/tabmodectl.h \
    TabMotion/tabmotion.h \
    itabwidget.h \
    TabModeCtl/modectlpanel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    plotunitgraph129.ui\
    tabctlpanel129.ui \
    DialogPickCurve/dialogpickcurve.ui \
    TabModeCtl/tabmodectl.ui \
    TabMotion/tabmotion.ui

TRANSLATIONS    += ch_plotunit.ts en_plotunit.ts
