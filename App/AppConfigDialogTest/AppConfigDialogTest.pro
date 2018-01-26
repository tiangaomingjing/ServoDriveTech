#-------------------------------------------------
#
# Project created by QtCreator 2018-01-25T15:53:04
#
#-------------------------------------------------
include(../App.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppConfigDialogTest
TEMPLATE = app


SOURCES += main.cpp\
        configmainwindow.cpp \
    configdialog.cpp \
    ../../Common/src/Kernel/deviceconfig.cpp

HEADERS  += configmainwindow.h \
    configdialog.h \
    ../../Common/src/Kernel/deviceconfig.h

FORMS    += configmainwindow.ui \
    configdialog.ui
