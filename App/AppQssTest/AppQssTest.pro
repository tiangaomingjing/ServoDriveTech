#-------------------------------------------------
#
# Project created by QtCreator 2017-12-22T17:02:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppQssTest
TEMPLATE = app


SOURCES += main.cpp\
        qssmainwindow.cpp \
    SystemInfo/syswin.cpp \
    stylewidget.cpp \
    gtdoublespinbox.cpp

HEADERS  += qssmainwindow.h \
    styleiconwidget.h \
    SystemInfo/isysinfo.h \
    SystemInfo/syswin.h \
    stylewidget.h \
    gtdoublespinbox.h

FORMS    += qssmainwindow.ui
