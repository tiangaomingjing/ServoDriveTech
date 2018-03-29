#-------------------------------------------------
#
# Project created by QtCreator 2018-03-29T19:31:22
#
#-------------------------------------------------
include(../App.pri)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppCustomPlotTest
TEMPLATE = app


SOURCES += main.cpp\
        customplotmainwindow.cpp

HEADERS  += customplotmainwindow.h

FORMS    += customplotmainwindow.ui
