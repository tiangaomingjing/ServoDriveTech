#-------------------------------------------------
#
# Project created by QtCreator 2017-11-29T16:45:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS_PATH=$${PWD}/../../Libs

INCLUDEPATH+=$${LIBS_PATH}/Com/Communication

TARGET = AppTest
TEMPLATE = app


SOURCES += main.cpp\
        appmainwindowtest.cpp

HEADERS  += appmainwindowtest.h

FORMS    += appmainwindowtest.ui
