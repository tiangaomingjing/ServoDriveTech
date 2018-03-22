#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T19:07:42
#
#-------------------------------------------------
include(../App.pri)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppAlarmLedTest
TEMPLATE = app


SOURCES += main.cpp\
        alarmledmainwindow.cpp \
    qflowlayout.cpp \
    ../../Common/src/ledalarm.cpp

HEADERS  += alarmledmainwindow.h \
    qflowlayout.h \
    ../../Common/src/ledalarm.h

FORMS    += alarmledmainwindow.ui
