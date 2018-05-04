#-------------------------------------------------
#
# Project created by QtCreator 2018-04-26T16:15:50
#
#-------------------------------------------------

include(../Libs.pri)
INCLUDEPATH+=$${PWD}/../GTUtils\
             $${PWD}/../GTUtils/QtTreeManager\
             $${PWD}/../GTUtils/BitItemHelper\
             $${PWD}/../SDKernel\
             $${PWD}/../Com\
             $${PWD}/../Com/Communication\

QT       += widgets core

QT       -= gui

TEMPLATE = lib

DEFINES += ADVUSER_LIBRARY

CONFIG(debug, debug|release){
    ADVUSR_OUT_PATH = $${APP_BUILD_PATH}/debug/bin
    LIBS +=$${ADVUSR_OUT_PATH}/GTUtilsd.lib\
           $${ADVUSR_OUT_PATH}/SDKerneld.lib
    TARGET = AdvUserd
} else{
    OPT_OUT_PATH=$${APP_BUILD_PATH}/release/bin
    LIBS +=$${ADVUSR_OUT_PATH}/GTUtils.lib\
           $${ADVUSR_OUT_PATH}/SDKernel.lib
    TARGET = AdvUser
}

DESTDIR =$${ADVUSR_OUT_PATH}

SOURCES += iadvuser.cpp \
    advusercheck.cpp \
    advusercontainer.cpp \
    advusermask.cpp

HEADERS += iadvuser.h\
        advuser_global.h \
    iadvuser_p.h \
    advusercheck.h \
    advusercontainer.h \
    advusermask.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    advusercheck.ui \
    advusermask.ui
