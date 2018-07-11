#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:55:16
#
#-------------------------------------------------
include (../UI.pri)

INCLUDEPATH +=$$PWD/IIRFilter

QT       += widgets

QT       -= gui

TEMPLATE = lib

DEFINES += UICURRENT_LIBRARY

CONFIG(debug, debug|release){
    TARGET = UiCurrentd
} else{
    TARGET = UiCurrent
}

SOURCES += uicurrent.cpp \
    graphcurrent129.cpp \
    graphcurrent130.cpp \
    graphcurrent133.cpp \
    IIRFilter/iirfilter.cpp

HEADERS += uicurrent.h\
        uicurrent_global.h \
    graphcurrent129.h \
    graphcurrent130.h \
    graphcurrent133.h \
    IIRFilter/iirfilter.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uicurrent.ui \
    graphcurrent129.ui \
    IIRFilter/iirfilter.ui

TRANSLATIONS    += ch_uicurrent.ts en_uicurrent.ts
