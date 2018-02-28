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
    widgetitem.cpp \
    arrowitem.cpp \
    interactiveview.cpp \
    targetitemwidget.cpp \
    anchoritemhelper.cpp

HEADERS  += widgetlayoutmainwindow.h \
    piditem.h \
    sumitem.h \
    sumitemwidget.h \
    widgetitem.h \
    arrowitem.h \
    interactiveview.h \
    targetitemwidget.h \
    anchoritemhelper.h

FORMS    += widgetlayoutmainwindow.ui
