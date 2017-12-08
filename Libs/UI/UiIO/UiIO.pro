#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:57:31
#
#-------------------------------------------------
include (../UI.pri)

QT       += widgets

QT       -= gui


TEMPLATE = lib

DEFINES += UIIO_LIBRARY

CONFIG(debug, debug|release){
    TARGET = UiIOd
} else{
    TARGET = UiIO
}

SOURCES += uiio.cpp

HEADERS += uiio.h\
        uiio_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uiio.ui
