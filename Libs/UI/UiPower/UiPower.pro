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

SOURCES += uipower.cpp \
    graphpower129.cpp

HEADERS += uipower.h\
        uipower_global.h \
    graphpower129.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uipower.ui \
    graphpower129.ui
