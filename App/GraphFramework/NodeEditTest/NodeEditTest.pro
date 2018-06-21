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
    nodeitem/nodeblock.cpp \
    nodeitem/nodeline.cpp \
    nodeitem/nodeport.cpp \
    nodeitem/inodeconnection.cpp \
    nodeitem/nodecornerline.cpp \
    nodeitem/nodequadline.cpp \
    nodeitem/nodeswitch.cpp

HEADERS  += nodeeditmainwindow.h \
    nodeitem/nodeitemglobaldef.h \
    nodeitem/nodeblock.h \
    nodeitem/nodeline.h \
    nodeitem/nodeport.h \
    nodeitem/inodeconnection.h \
    nodeitem/nodecornerline.h \
    nodeitem/nodequadline.h \
    nodeitem/nodeswitch.h

FORMS    += nodeeditmainwindow.ui
