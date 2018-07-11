#-------------------------------------------------
#
# Project created by QtCreator 2018-02-09T16:42:23
#
#-------------------------------------------------
include(../Libs.pri)
QT       -= gui
QT        +=widgets

INCLUDEPATH+=$${PWD}/../com/Communication

TEMPLATE = lib

BUILD_PATH=$${APP_BUILD_PATH}

CONFIG(debug, debug|release){
    CMD_OUT_PATH = $${BUILD_PATH}/debug/bin
    LIBS+=
    TARGET = Cmdd
} else{
    CMD_OUT_PATH = $${BUILD_PATH}/release/bin
    LIBS+=
    TARGET = Cmd
}
DESTDIR =$${CMD_OUT_PATH}

DEFINES += CMD_LIBRARY

SOURCES += \
    generalcmd.cpp

HEADERS +=\
        cmd_global.h \
    generalcmd.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
