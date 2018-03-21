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
    ledalarm.cpp \
    qflowlayout.cpp

HEADERS  += alarmledmainwindow.h \
    ledalarm.h \
    qflowlayout.h

FORMS    += alarmledmainwindow.ui
