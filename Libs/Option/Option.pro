#-------------------------------------------------
#
# Project created by QtCreator 2017-12-21T17:11:09
#
#-------------------------------------------------
include(../Libs.pri)
INCLUDEPATH+=$${PWD}/../GTUtils\
            $${PWD}/../GTUtils/QtTreeManager\

QT       += widgets core

QT       -= gui

TEMPLATE = lib

DEFINES += OPTION_LIBRARY

CONFIG(debug, debug|release){
    OPT_OUT_PATH=$${APP_BUILD_PATH}/debug/bin
    LIBS +=$${OPT_OUT_PATH}/GTUtilsd.lib
    TARGET = Optiond
} else{
    OPT_OUT_PATH=$${APP_BUILD_PATH}/release/bin
    LIBS +=$${OPT_OUT_PATH}/GTUtils.lib
    TARGET = Option
}
DESTDIR =$${OPT_OUT_PATH}

SOURCES += \
    optcontainer.cpp \
    iopt.cpp \
    optuser.cpp \
    optface.cpp \
    optplot.cpp \
    optautoload.cpp \
    qmlstylehelper.cpp

HEADERS +=\
        option_global.h \
    optcontainer.h \
    iopt.h \
    iopt_p.h \
    optuser.h \
    optface.h \
    optplot.h \
    optautoload.h \
    qmlstylehelper.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    optuser.ui \
    optface.ui \
    optplot.ui \
    optautoload.ui
