#-------------------------------------------------
#
# Project created by QtCreator 2018-04-10T15:10:48
#
#-------------------------------------------------
INCLUDEPATH +=$${PWD}/../../Libs/PlotUnit/PlotUnitGraph\
              $${PWD}/../../Libs/PlotUnit/PlotUnitGraph/TabModeCtl

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppPlotTest
TEMPLATE = app


SOURCES += main.cpp\
        plotmainwindow.cpp \
    axismodewidget.cpp \
    ../../Libs/PlotUnit/PlotUnitGraph/TabModeCtl/modectlpanel.cpp

HEADERS  += plotmainwindow.h \
    axismodewidget.h \
    ../../Libs/PlotUnit/PlotUnitGraph/TabModeCtl/modectlpanel.h

FORMS    += plotmainwindow.ui
