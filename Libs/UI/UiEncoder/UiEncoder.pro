#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:54:40
#
#-------------------------------------------------
include (../UI.pri)

QT       += widgets

QT       -= gui

TARGET = UiEncoder
TEMPLATE = lib

DEFINES += UIENCODER_LIBRARY

CONFIG(debug, debug|release){
    TARGET = UiEncoderd
} else{
    TARGET = UiEncoder
}

SOURCES += uiencoder.cpp \
    graphencoder129.cpp

HEADERS += uiencoder.h\
        uiencoder_global.h \
    graphencoder129.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uiencoder.ui \
    graphencoder129.ui
