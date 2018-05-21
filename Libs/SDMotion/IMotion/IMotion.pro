#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T13:58:17
#
#-------------------------------------------------
include(../Motion.pri)
QT       -= gui

TEMPLATE = lib

CONFIG(debug, debug|release){
    TARGET = IMotiond
} else{
    TARGET = IMotion
}


DEFINES += IMOTION_LIBRARY

SOURCES += imotion.cpp

HEADERS += imotion.h\
        imotion_global.h \
    imotion_p.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
