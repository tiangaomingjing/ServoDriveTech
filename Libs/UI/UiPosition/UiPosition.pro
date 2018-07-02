#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:55:52
#
#-------------------------------------------------
include (../UI.pri)

QT       += widgets

QT       -= gui

TEMPLATE = lib

DEFINES += UIPOSITION_LIBRARY

CONFIG(debug, debug|release){
    TARGET = UiPositiond
} else{
    TARGET = UiPosition
}

SOURCES += uiposition.cpp \
    graphposition129.cpp\
    graphposition133.cpp \
    posinputfilter.cpp \
    pospid133.cpp

HEADERS += uiposition.h\
        uiposition_global.h \
    graphposition129.h\
    graphposition133.h \
    posinputfilter.h \
    pospid133.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uiposition.ui \
    graphposition129.ui \
    posinputfilter.ui \
    pospid133.ui
