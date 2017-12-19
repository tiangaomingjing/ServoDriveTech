#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T11:42:48
#
#-------------------------------------------------
include(../App.pri)
QT       += core gui qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TEMPLATE = app

CONFIG(debug, debug|release){
  TARGET = AppUiTestd
} else{
  TARGET = AppUiTest
}

SOURCES += main.cpp\
        uimainwindow.cpp \
    ../../Common/src/Kernel/devcomrwriter.cpp \
    ../../Common/src/Kernel/devtextrwriter.cpp \
    ../../Common/src/Kernel/gconfigreadwriter.cpp \
    ../../Common/src/Kernel/globalconfig.cpp \
    ../../Common/src/Kernel/idevreadwriter.cpp \
    ../../Common/src/Kernel/iuicontroler.cpp \
    ../../Common/src/Kernel/sdassembly.cpp \
    ../../Common/src/Kernel/sevuicontroler.cpp \
    ../../Common/src/UiFactory/uifactory.cpp \
    ../../Common/src/Kernel/globaluicontroler.cpp \
    ../../Common/src/Kernel/deviceconfig.cpp

HEADERS  += uimainwindow.h \
    ../../Common/src/sdtglobaldef.h \
    ../../Common/src/Kernel/devcomrwriter.h \
    ../../Common/src/Kernel/devtextrwriter.h \
    ../../Common/src/Kernel/gconfigreadwriter.h \
    ../../Common/src/Kernel/globalconfig.h \
    ../../Common/src/Kernel/idevreadwriter.h \
    ../../Common/src/Kernel/iuicontroler.h \
    ../../Common/src/Kernel/sdassembly.h \
    ../../Common/src/Kernel/sevuicontroler.h \
    ../../Common/src/UiFactory/uifactory.h \
    ../../Common/src/UiFactory/registerfunction.h \
    ../../Common/src/Kernel/globaluicontroler.h \
    ../../Common/src/Kernel/deviceconfig.h

FORMS    += uimainwindow.ui

DISTFILES += \
    ../../Common/src/QML/V129/UiBrake.qml \
    ../../Common/src/QML/V129/UiCurrent.qml \
    ../../Common/src/QML/V129/UiEncoder.qml \
    ../../Common/src/QML/V129/UiMotor.qml \
    ../../Common/src/QML/V129/UiPosition.qml \
    ../../Common/src/QML/V129/UiPower.qml \
    ../../Common/src/QML/V129/UiSpeed.qml \
    ../../Common/src/QML/V129/UiStatus.qml
