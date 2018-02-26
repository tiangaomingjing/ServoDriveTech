#-------------------------------------------------
#
# Project created by QtCreator 2018-02-21T23:14:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphWidgetLayoutTest
TEMPLATE = app


SOURCES += main.cpp\
        widgetlayoutmainwindow.cpp \
    piditem.cpp \
    sumitem.cpp \
    sumitemwidget.cpp \
    arrow.cpp

HEADERS  += widgetlayoutmainwindow.h \
    piditem.h \
    sumitem.h \
    sumitemwidget.h \
    arrow.h

FORMS    += widgetlayoutmainwindow.ui
