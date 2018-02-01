#-------------------------------------------------
#
# Project created by QtCreator 2017-12-18T14:23:48
#
#-------------------------------------------------
include(../Libs.pri)

QT+=widgets
QT       -= gui

INCLUDEPATH+=$${PWD}/../GTUtils\
            $${PWD}/../GTUtils/QtTreeManager\
            $${PWD}/../GTUtils/DeviceIdHelper\
            $${PWD}/../Com/Communication\
            $${PWD}/../../Common/src\
            $${PWD}/../../Common/src/kernel\
            $${PWD}/../../Common/src/SdtGlobal

TEMPLATE = lib

DEFINES += SDKERNEL_LIBRARY

CONFIG(debug, debug|release){
    SDKERNEL_OUT_PATH = $${APP_BUILD_PATH}/debug/bin
    LIBS+=$${SDKERNEL_OUT_PATH}/Communicationd.lib\
          $${SDKERNEL_OUT_PATH}/GTUtilsd.lib

    TARGET = SDKerneld
} else{
    SDKERNEL_OUT_PATH = $${APP_BUILD_PATH}/release/bin
    LIBS+=$${SDKERNEL_OUT_PATH}/Communication.lib\
          $${SDKERNEL_OUT_PATH}/GTUtils.lib
    TARGET = SDKernel
}
DESTDIR =$${SDKERNEL_OUT_PATH}

SOURCES += \
    axistreemap.cpp \
    ictrboard.cpp \
    idspmap.cpp \
    ipwrboard.cpp \
    linksocket.cpp \
    sevctrboard.cpp \
    sevdevice.cpp \
    sevdspmap.cpp \
    sevpwrboard.cpp \
    PowerTreeManage/powertreemanage.cpp \
    ../../Common/src/Kernel/deviceconfig.cpp \
    sdkernel_global.cpp \
    verattribute.cpp

HEADERS += \
    sdkernel_global.h \
    axistreemap.h \
    ictrboard.h \
    idspmap.h \
    ipwrboard.h \
    linksocket.h \
    sevctrboard.h \
    sevdevice.h \
    sevdeviceprivate_p.h \
    sevdspmap.h \
    sevpwrboard.h \
    PowerTreeManage/powertreemanage.h \
    ../../Common/src/Kernel/deviceconfig.h \
    verattribute.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
