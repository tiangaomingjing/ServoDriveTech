#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:55:34
#
#-------------------------------------------------
include (../UI.pri)

QT       += widgets

QT       -= gui

TEMPLATE = lib

DEFINES += UIVELOCITY_LIBRARY

CONFIG(debug, debug|release){
    TARGET = UiVelocityd
} else{
    TARGET = UiVelocity
}

SOURCES += uivelocity.cpp

HEADERS += uivelocity.h\
        uivelocity_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uivelocity.ui
