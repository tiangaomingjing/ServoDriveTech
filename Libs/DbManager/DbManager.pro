#-------------------------------------------------
#
# Project created by QtCreator 2018-05-28T17:11:22
#
#-------------------------------------------------

include(../Libs.pri)

QT       += sql

QT       -= gui

TEMPLATE = lib

DEFINES += DBMANAGER_LIBRARY

SOURCES += dbmanager.cpp

HEADERS += dbmanager.h\
        dbmanager_global.h

CONFIG(debug, debug|release){
    DB_OUT_PATH=$${APP_BUILD_PATH}/debug/bin
    TARGET = DbManagerd
} else{
    DB_OUT_PATH=$${APP_BUILD_PATH}/release/bin
    TARGET = DbManager
}

DESTDIR =$${DB_OUT_PATH}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
