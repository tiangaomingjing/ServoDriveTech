#-------------------------------------------------
#
# Project created by QtCreator 2017-12-01T11:14:00
#
#-------------------------------------------------

include(../Libs.pri)
UtilsTest=0
isEqual(UtilsTest,1){
  BUILD_PATH=$${PWD}/build/
}
isEqual(UtilsTest,0){
  BUILD_PATH=$${APP_BUILD_PATH}
}


QT +=designer
QT       -= gui

TEMPLATE = lib

DEFINES += GTUTILS_LIBRARY

CONFIG(debug, debug|release){
    LIBS +=
    UTILS_OUT_PATH=$${BUILD_PATH}/debug/bin
    TARGET = GTUtilsd
} else{
    LIBS +=
    UTILS_OUT_PATH=$${BUILD_PATH}/release/bin
    TARGET = GTUtils
}
DESTDIR =$${UTILS_OUT_PATH}


SOURCES += \
    QtTreeManager/qttreemanager.cpp \
    gtutils.cpp

HEADERS +=\
    QtTreeManager/qttreemanager.h \
    gtutils_global.h \
    gtutils.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
