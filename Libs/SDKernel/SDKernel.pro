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
            $${PWD}/../GTUtils/IFRamManager\
            $${PWD}/../GTUtils/CmdManager\
            $${PWD}/../AdvUser\
            $${PWD}/../Option\
            $${PWD}/../Com/Communication\
            $${PWD}/../../Common/src\
            $${PWD}/../../Common/src/Kernel\
            $${PWD}/../../Common/src/SdtGlobal

TEMPLATE = lib

DEFINES += SDKERNEL_LIBRARY

CONFIG(debug, debug|release){
    SDKERNEL_OUT_PATH = $${APP_BUILD_PATH}/debug/bin
    LIBS+=$${SDKERNEL_OUT_PATH}/Communicationd.lib\
          $${SDKERNEL_OUT_PATH}/GTUtilsd.lib\
          $${SDKERNEL_OUT_PATH}/Optiond.lib\
          $${SDKERNEL_OUT_PATH}/AdvUserd.lib

    TARGET = SDKerneld
} else{
    SDKERNEL_OUT_PATH = $${APP_BUILD_PATH}/release/bin
    LIBS+=$${SDKERNEL_OUT_PATH}/Communication.lib\
          $${SDKERNEL_OUT_PATH}/GTUtils.lib\
          $${SDKERNEL_OUT_PATH}/Option.lib\
          $${SDKERNEL_OUT_PATH}/AdvUser.lib

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
    verattribute.cpp \
    generalcmd.cpp \
    sevsearchphasehelper.cpp

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
    verattribute.h \
    generalcmd.h \
    sevsearchphasehelper.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
TRANSLATIONS    += ch_sdkernel.ts en_sdkernel.ts
