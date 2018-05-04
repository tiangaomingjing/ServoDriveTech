QT += core widgets
QT -= gui

TARGET = src
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH+=../../Libs/Com/Communication\
              ../../Libs/GTUtils/QtTreeManager\
              ../../Libs/GTUtils/DeviceIdHelper\
              ../../Libs/GTUtils/SelfBuilder\
              ../../Libs/GTUtils\
              ../../Libs/UI\
              ../../Libs/UI/IUiWidget\
              ../../Libs/SDKernel\
              ../../Libs/Option\
              ../../Libs/PlotUnit/PlotUnitGraph\
              ../../Libs/PlotUnit/IPlotUnit\
              $${PWD}/../../Libs/PlotCurvePluginFramework/ICurve\
              $${PWD}/UiFactory\
              $${PWD}/Kernel\
              $${PWD}/SdtGlobal

CONFIG(debug, debug|release){
    COMMONSRC_OUT_PATH=$${PWD}/../../build/debug/bin
    QML_IMPORT_PATH +=$${PWD}/../../build/debug/custom/option/qmlstyle
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
          -lSDKerneld\
          -lOptiond\
          -lPlotUnitGraphd\
          -lIPlotUnitd
    TARGET = CommonSrcAppd
} else{
    COMMONSRC_OUT_PATH=$${PWD}/../../build/release/bin
    QML_IMPORT_PATH +=$${PWD}/../../build/release/custom/option/qmlstyle
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
          -lSDKernel\
          -lOption\
          -lPlotUnitGraph\
          -lIPlotUnit
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
    test.c \
    SdtGlobal/sdtglobaldef.cpp \
    Kernel/sdterror.cpp \
    ledalarm.cpp


HEADERS += \
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
    test.h \
    SdtGlobal/sdtglobaldef.h \
    Kernel/sdterror.h \
    ledalarm.h

DISTFILES += \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/qmldir \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/IStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/StyleLoader.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/BlackStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/blue/BlueStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/UiBrakeStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/UiCurrentStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/UiEncoderStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/UiMotorStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/UiPositionStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/UiPowerStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/UiSpeedStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/UiStatusStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/UiVelocityStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/blue/UiBrakeStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/blue/UiCurrentStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/blue/UiEncoderStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/blue/UiMotorStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/blue/UiPositionStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/blue/UiSpeedStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/blue/UiStatusStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/blue/UiVelocityStyle.qml \
    QML/SD4x/V129/UiBrake.qml \
    QML/SD4x/V129/UiCurrent.qml \
    QML/SD4x/V129/UiEncoder.qml \
    QML/SD4x/V129/UiMotor.qml \
    QML/SD4x/V129/UiPosition.qml \
    QML/SD4x/V129/UiPower.qml \
    QML/SD4x/V129/UiSpeed.qml \
    QML/SD4x/V129/UiStatus.qml \
    QML/SD4x/V129/UiVelocity.qml




