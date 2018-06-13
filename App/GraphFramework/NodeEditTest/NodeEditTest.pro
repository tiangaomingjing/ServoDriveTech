#-------------------------------------------------
#
# Project created by QtCreator 2018-06-13T10:24:44
#
#-------------------------------------------------
INCLUDEPATH += $$PWD/nodeitem

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NodeEditTest
TEMPLATE = app


SOURCES += main.cpp\
        nodeeditmainwindow.cpp \
    nodeitem/qneblock.cpp \
    nodeitem/qneconnection.cpp \
    nodeitem/qneport.cpp

HEADERS  += nodeeditmainwindow.h \
    nodeitem/qneblock.h \
    nodeitem/qneconnection.h \
    nodeitem/qneport.h \
    nodeitem/nodeitemglobaldef.h

FORMS    += nodeeditmainwindow.ui
