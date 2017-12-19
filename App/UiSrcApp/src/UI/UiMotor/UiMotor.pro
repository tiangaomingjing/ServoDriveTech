#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:53:43
#
#-------------------------------------------------
include (../UI.pri)

QT       += widgets

QT       -= gui


TEMPLATE = lib

DEFINES += UIMOTOR_LIBRARY

CONFIG(debug, debug|release){
    TARGET = UiMotord
} else{
    TARGET = UiMotor
}

SOURCES += uimotor.cpp

HEADERS += uimotor.h\
        uimotor_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uimotor.ui
