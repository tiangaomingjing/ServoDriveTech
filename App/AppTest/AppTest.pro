#-------------------------------------------------
#
# Project created by QtCreator 2017-11-29T16:45:34
#
#-------------------------------------------------
include(../App.pri)

QT       += core gui qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG+=console
CONFIG -= app_bundle

TEMPLATE = app

CONFIG(debug, debug|release){
    TARGET = AppTestd
} else{
    TARGET = AppTest
}


SOURCES += main.cpp\
        appmainwindowtest.cpp \
    changframaddr.cpp \
    ../../Common/src/Kernel/devcomrwriter.cpp \
    ../../Common/src/Kernel/deviceconfig.cpp \
    ../../Common/src/Kernel/devtextrwriter.cpp \
    ../../Common/src/Kernel/gconfigreadwriter.cpp \
    ../../Common/src/Kernel/globalconfig.cpp \
    ../../Common/src/Kernel/globaluicontroler.cpp \
    ../../Common/src/Kernel/idevreadwriter.cpp \
    ../../Common/src/Kernel/iuicontroler.cpp \
    ../../Common/src/Kernel/sdassembly.cpp \
    ../../Common/src/Kernel/sevuicontroler.cpp \
    ../../Common/src/UiFactory/uifactory.cpp\
    ../../Common/src/SdtGlobal/sdtglobaldef.cpp


HEADERS  += appmainwindowtest.h \
    changframaddr.h \
    ../../Common/src/Kernel/devcomrwriter.h \
    ../../Common/src/Kernel/deviceconfig.h \
    ../../Common/src/Kernel/devtextrwriter.h \
    ../../Common/src/Kernel/gconfigreadwriter.h \
    ../../Common/src/Kernel/globalconfig.h \
    ../../Common/src/Kernel/globaluicontroler.h \
    ../../Common/src/Kernel/idevreadwriter.h \
    ../../Common/src/Kernel/iuicontroler.h \
    ../../Common/src/Kernel/sdassembly.h \
    ../../Common/src/Kernel/sevuicontroler.h \
    ../../Common/src/UiFactory/registerfunction.h \
    ../../Common/src/UiFactory/uifactory.h \
    ../../Common/src/SdtGlobal/sdtglobaldef.h

FORMS    += appmainwindowtest.ui
