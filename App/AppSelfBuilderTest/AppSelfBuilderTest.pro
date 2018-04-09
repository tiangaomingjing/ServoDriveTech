#-------------------------------------------------
#
# Project created by QtCreator 2018-04-03T14:38:35
#
#-------------------------------------------------
include(../App.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppSelfBuilderTest
TEMPLATE = app


SOURCES += main.cpp\
        selfbuildermainwindow.cpp

HEADERS  += selfbuildermainwindow.h

FORMS    += selfbuildermainwindow.ui
