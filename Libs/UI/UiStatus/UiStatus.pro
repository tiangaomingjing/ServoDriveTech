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

SOURCES += uistatus.cpp \
    graphstatus129.cpp

HEADERS += uistatus.h\
        uistatus_global.h \
    graphstatus129.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uistatus.ui \
    graphstatus129.ui

TRANSLATIONS    += ch_uistatus.ts en_uistatus.ts
