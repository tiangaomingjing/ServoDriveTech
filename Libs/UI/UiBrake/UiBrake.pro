#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:57:00
#
#-------------------------------------------------
include (../UI.pri)
QT       += widgets

QT       -= gui

TEMPLATE = lib

DEFINES += UIBRAKE_LIBRARY

CONFIG(debug, debug|release){
    TARGET = UiBraked
} else{
    TARGET = UiBrake
}

SOURCES += uibrake.cpp \
    graphbrake129.cpp

HEADERS += uibrake.h\
        uibrake_global.h \
    graphbrake129.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uibrake.ui \
    graphbrake129.ui

RESOURCES +=
