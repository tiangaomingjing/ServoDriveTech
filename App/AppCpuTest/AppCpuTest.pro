#-------------------------------------------------
#
# Project created by QtCreator 2018-01-05T15:03:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppCpuTest
TEMPLATE = app


SOURCES += main.cpp\
        cpumainwindow.cpp \
    SystemInfo/syswin.cpp

HEADERS  += cpumainwindow.h \
    SystemInfo/isysinfo.h \
    SystemInfo/syswin.h

FORMS    += cpumainwindow.ui
