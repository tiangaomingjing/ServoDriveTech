#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T13:58:17
#
#-------------------------------------------------
QT       -= gui
QT    +=widgets

TEMPLATE = lib

include(../../Libs.pri)
INCLUDEPATH +=$$PWD/../../GTUtils\
              $$PWD/../../Option\
              $$PWD/../../SDKernel\
              $$PWD/../../Com/Communication


CONFIG(debug, debug|release){
    MOTION_OUT_PATH = $${APP_BUILD_PATH}/debug/bin
    LIBS+=\
          $${MOTION_OUT_PATH}/GTUtilsd.lib\
          $${MOTION_OUT_PATH}/Optiond.lib\
          $${MOTION_OUT_PATH}/SDKerneld.lib
    TARGET = IMotiond
} else{
    MOTION_OUT_PATH = $${APP_BUILD_PATH}/release/bin
    LIBS+=\
          $${MOTION_OUT_PATH}/GTUtils.lib\
          $${MOTION_OUT_PATH}/Option.lib\
          $${MOTION_OUT_PATH}/SDKernel.lib
    TARGET = IMotion
}
DESTDIR =$${MOTION_OUT_PATH}


DEFINES += IMOTION_LIBRARY

SOURCES += imotion.cpp

HEADERS += imotion.h\
        imotion_global.h \
    imotion_p.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
