#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:56:41
#
#-------------------------------------------------
include (../UI.pri)

QT       += widgets

QT       -= gui

TEMPLATE = lib

DEFINES += UIFLASH_LIBRARY

CONFIG(debug, debug|release){
    TARGET = UiFLASHd
} else{
    TARGET = UiFLASH
}

SOURCES += uiflash.cpp

HEADERS += uiflash.h\
        uiflash_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uiflash.ui
