#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:56:25
#
#-------------------------------------------------
include (../UI.pri)

QT       += widgets

QT       -= gui

TEMPLATE = lib

DEFINES += UIRAM_LIBRARY

CONFIG(debug, debug|release){
    TARGET = UiRAMd
} else{
    TARGET = UiRAM
}

SOURCES += uiram.cpp

HEADERS += uiram.h\
        uiram_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uiram.ui
