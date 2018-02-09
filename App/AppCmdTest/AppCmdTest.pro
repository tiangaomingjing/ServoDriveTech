#-------------------------------------------------
#
# Project created by QtCreator 2018-02-09T17:48:23
#
#-------------------------------------------------
include(../App.pri)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG(debug, debug|release){
  TARGET = AppCmdTestd
} else{
  TARGET = AppCmdTest
}

SOURCES += main.cpp\
        cmdmainwindow.cpp

HEADERS  += cmdmainwindow.h

FORMS    += cmdmainwindow.ui
