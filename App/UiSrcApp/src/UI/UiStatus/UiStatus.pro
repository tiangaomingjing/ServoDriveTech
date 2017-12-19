#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:56:08
#
#-------------------------------------------------
include (../UI.pri)

QT       += widgets

QT       -= gui

TEMPLATE = lib

DEFINES += UISTATUS_LIBRARY

CONFIG(debug, debug|release){
    TARGET = UiStatusd
} else{
    TARGET = UiStatus
}

SOURCES += uistatus.cpp

HEADERS += uistatus.h\
        uistatus_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uistatus.ui
