#-------------------------------------------------
#
# Project created by QtCreator 2018-01-25T15:53:04
#
#-------------------------------------------------
include(../App.pri)
INCLUDEPATH+=$${PWD}/../AppSDT/ConfigDialog

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppConfigDialogTest
TEMPLATE = app


SOURCES += main.cpp\
        configmainwindow.cpp \
    ../../Common/src/Kernel/deviceconfig.cpp \
    ../AppSDT/ConfigDialog/configdialog.cpp

HEADERS  += configmainwindow.h \
    ../../Common/src/Kernel/deviceconfig.h \
    ../AppSDT/ConfigDialog/configdialog.h

FORMS    += configmainwindow.ui \
    ../AppSDT/ConfigDialog/configdialog.ui
