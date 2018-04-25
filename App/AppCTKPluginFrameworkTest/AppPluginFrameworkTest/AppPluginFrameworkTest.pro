#-------------------------------------------------
#
# Project created by QtCreator 2018-04-17T17:46:47
#
#-------------------------------------------------
INCLUDEPATH +=$$PWD/../Plugins/IPlotCurve

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TEMPLATE = app
include (../CTK.pri)

CONFIG(debug, debug|release){
  TARGET = AppPluginFrameworkTestd
} else{
  TARGET = AppPluginFrameworkTest
}

SOURCES += main.cpp\
        pluginframeworkmainwindow.cpp

HEADERS  += pluginframeworkmainwindow.h

FORMS    += pluginframeworkmainwindow.ui
