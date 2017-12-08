#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:54:59
#
#-------------------------------------------------
include (../UI.pri)

QT       += widgets

QT       -= gui


TEMPLATE = lib

DEFINES += UIPOWER_LIBRARY

CONFIG(debug, debug|release){
    TARGET = UiPowerd
} else{
    TARGET = UiPower
}

SOURCES += uipower.cpp

HEADERS += uipower.h\
        uipower_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uipower.ui
