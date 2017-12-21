QT += core widgets
QT -= gui

TARGET = src
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH+=../../Libs/Com/Communication\
              ../../Libs/GTUtils/QtTreeManager\
              ../../Libs/GTUtils\
              ../../Libs/UI\
              ../../Libs/UI/IUiWidget\
              ../../Libs/SDKernel

CONFIG(debug, debug|release){
    COMMONSRC_OUT_PATH=$${PWD}/../../build/debug/bin
    LIBPATH=$${COMMONSRC_OUT_PATH}
    LIBS +=-lCommunicationd\
          -lGTUtilsd\
          -lIUiWidgetd\
          -lUiBraked\
          -lUiCurrentd\
          -lUiEncoderd\
          -lUiFLASHd\
          -lUiIOd\
          -lUiMotord\
          -lUiPlotd\
          -lUiPositiond\
          -lUiPowerd\
          -lUiRAMd\
          -lUiStatusd\
          -lUiVelocityd\
          -lSDKerneld
    TARGET = CommonSrcAppd
} else{
    COMMONSRC_OUT_PATH=$${PWD}/../../build/release/bin
    LIBPATH=$${COMMONSRC_OUT_PATH}
#    LIBS +=$${COMMONSRC_OUT_PATH}\Communication.lib\
#           $${COMMONSRC_OUT_PATH}\GTUtils.lib
    LIBS +=-lCommunication\
          -lGTUtils\
          -lIUiWidget\
          -lUiBrake\
          -lUiCurrent\
          -lUiEncoder\
          -lUiFLASH\
          -lUiIO\
          -lUiMotor\
          -lUiPlot\
          -lUiPosition\
          -lUiPower\
          -lUiRAM\
          -lUiStatus\
          -lUiVelocity\
          -lSDKernel
    TARGET = CommonSrcApp
}
DESTDIR =$${COMMONSRC_OUT_PATH}

SOURCES += main.cpp \
    Kernel/idevreadwriter.cpp \
    Kernel/iuicontroler.cpp \
    Kernel/sevuicontroler.cpp \
    Kernel/sdassembly.cpp \
    Kernel/globalconfig.cpp \
    Kernel/gconfigreadwriter.cpp \
    Kernel/devtextrwriter.cpp \
    Kernel/devcomrwriter.cpp \
    Kernel/deviceconfig.cpp \
    UiFactory/uifactory.cpp \
    Kernel/globaluicontroler.cpp \
    Kernel/deviceidhelper.cpp


HEADERS += \
    sdtglobaldef.h \
    Kernel/idevreadwriter.h \
    Kernel/iuicontroler.h \
    Kernel/sevuicontroler.h \
    Kernel/sdassembly.h \
    Kernel/globalconfig.h \
    Kernel/gconfigreadwriter.h \
    Kernel/devtextrwriter.h \
    Kernel/devcomrwriter.h \
    Kernel/deviceconfig.h \
    UiFactory/uifactory.h \
    UiFactory/registerfunction.h \
    Kernel/globaluicontroler.h \
    Kernel/deviceidhelper.h

DISTFILES += \
    QML/V129/UiMotor.qml \
    QML/V129/UiBrake.qml \
    QML/V129/UiCurrent.qml \
    QML/V129/UiEncoder.qml \
    QML/V129/UiPosition.qml \
    QML/V129/UiPower.qml \
    QML/V129/UiSpeed.qml \
    QML/V129/UiStatus.qml \
    QML/V129/UiVelocity.qml



