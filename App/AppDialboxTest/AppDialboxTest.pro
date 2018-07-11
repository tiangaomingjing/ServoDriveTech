#-------------------------------------------------
#
# Project created by QtCreator 2018-02-06T09:25:35
#
#-------------------------------------------------
include(../../Libs/ThirdParty/qwt6.1.2/qwtlibs.pri)
include(../App.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppDialboxTest
TEMPLATE = app


SOURCES += main.cpp\
        dialmainwindow.cpp \
    dialbox.cpp

HEADERS  += dialmainwindow.h \
    dialbox.h

FORMS    += dialmainwindow.ui
