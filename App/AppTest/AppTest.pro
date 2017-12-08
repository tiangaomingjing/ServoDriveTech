#-------------------------------------------------
#
# Project created by QtCreator 2017-11-29T16:45:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS_PATH=$${PWD}/../../Libs
COMMON_PATH=$${PWD}/../../Common

INCLUDEPATH+=$${LIBS_PATH}/Com/Communication\
             $${LIBS_PATH}/GTUtils\
             $${LIBS_PATH}/GTUtils/QtTreeManager\
             $${COMMON_PATH}/src

TEMPLATE = app

CONFIG(debug, debug|release){
    APPTEST_OUT_PATH=$${PWD}/../../build/debug/bin
    LIBPATH=$${APPTEST_OUT_PATH}
    LIBS +=-lCommunicationd\
           -lGTUtilsd
    TARGET = AppTestd
} else{
    APPTEST_OUT_PATH=$${PWD}/../../build/release/bin
    LIBPATH=$${APPTEST_OUT_PATH}
#    LIBS +=$${APPTEST_OUT_PATH}\Communication.lib\
#           $${APPTEST_OUT_PATH}\GTUtils.lib
    LIBS +=-lCommunication\
           -lGTUtils
    TARGET = AppTest
}
DESTDIR =$${APPTEST_OUT_PATH}




SOURCES += main.cpp\
        appmainwindowtest.cpp \
    ../../Common/src/Kernel/axistreemap.cpp \
    ../../Common/src/Kernel/devcomrwriter.cpp \
    ../../Common/src/Kernel/deviceconfig.cpp \
    ../../Common/src/Kernel/devtextrwriter.cpp \
    ../../Common/src/Kernel/gconfigreadwriter.cpp \
    ../../Common/src/Kernel/globalconfig.cpp \
    ../../Common/src/Kernel/ictrboard.cpp \
    ../../Common/src/Kernel/idevreadwriter.cpp \
    ../../Common/src/Kernel/idspmap.cpp \
    ../../Common/src/Kernel/ipwrboard.cpp \
    ../../Common/src/Kernel/iuicontroler.cpp \
    ../../Common/src/Kernel/linksocket.cpp \
    ../../Common/src/Kernel/sdassembly.cpp \
    ../../Common/src/Kernel/sevdevice.cpp \
    ../../Common/src/Kernel/sevdspmap.cpp \
    ../../Common/src/Kernel/sevpwrboard.cpp \
    ../../Common/src/Kernel/sevuicontroler.cpp \
    ../../Common/src/Kernel/PowerTreeManage/powertreemanage.cpp \
    ../../Common/src/Kernel/sevctrboard.cpp

HEADERS  += appmainwindowtest.h \
    ../../Common/src/Kernel/axistreemap.h \
    ../../Common/src/Kernel/devcomrwriter.h \
    ../../Common/src/Kernel/deviceconfig.h \
    ../../Common/src/Kernel/devtextrwriter.h \
    ../../Common/src/Kernel/gconfigreadwriter.h \
    ../../Common/src/Kernel/globalconfig.h \
    ../../Common/src/Kernel/ictrboard.h \
    ../../Common/src/Kernel/idevreadwriter.h \
    ../../Common/src/Kernel/idspmap.h \
    ../../Common/src/Kernel/ipwrboard.h \
    ../../Common/src/Kernel/iuicontroler.h \
    ../../Common/src/Kernel/linksocket.h \
    ../../Common/src/Kernel/sdassembly.h \
    ../../Common/src/Kernel/sevdevice.h \
    ../../Common/src/Kernel/sevdeviceprivate_p.h \
    ../../Common/src/Kernel/sevdspmap.h \
    ../../Common/src/Kernel/sevpwrboard.h \
    ../../Common/src/Kernel/sevuicontroler.h \
    ../../Common/src/sdtglobaldef.h \
    ../../Common/src/Kernel/PowerTreeManage/powertreemanage.h \
    ../../Common/src/Kernel/sevctrboard.h

FORMS    += appmainwindowtest.ui
