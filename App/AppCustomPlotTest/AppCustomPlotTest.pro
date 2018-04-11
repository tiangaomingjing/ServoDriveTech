#-------------------------------------------------
#
# Project created by QtCreator 2018-03-29T19:31:22
#
#-------------------------------------------------
QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH +=$${PWD}/../../Libs/PlotUnit/PlotUnitGraph

TARGET = AppCustomPlotTest
TEMPLATE = app


SOURCES += main.cpp\
        customplotmainwindow.cpp \
    ../../Libs/PlotUnit/PlotUnitGraph/gtplot.cpp \
    ../../Libs/PlotUnit/PlotUnitGraph/qcpitemhandletag.cpp \
    ../../Libs/PlotUnit/PlotUnitGraph/qcpitemmeasure.cpp \
    ../../Libs/PlotUnit/PlotUnitGraph/qcustomplot.cpp

HEADERS  += customplotmainwindow.h \
    ../../Libs/PlotUnit/PlotUnitGraph/gtplot.h \
    ../../Libs/PlotUnit/PlotUnitGraph/qcpitemhandletag.h \
    ../../Libs/PlotUnit/PlotUnitGraph/qcpitemmeasure.h \
    ../../Libs/PlotUnit/PlotUnitGraph/qcustomplot.h

FORMS    += customplotmainwindow.ui
