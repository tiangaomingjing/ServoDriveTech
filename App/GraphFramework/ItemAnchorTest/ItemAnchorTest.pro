#-------------------------------------------------
#
# Project created by QtCreator 2018-02-28T17:19:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ItemAnchorTest
TEMPLATE = app


SOURCES += main.cpp\
        anchormainwindow.cpp \
    ../GraphWidgetLayoutTest/anchoritemhelper.cpp

HEADERS  += anchormainwindow.h \
    ../GraphWidgetLayoutTest/anchoritemhelper.h

FORMS    += anchormainwindow.ui
