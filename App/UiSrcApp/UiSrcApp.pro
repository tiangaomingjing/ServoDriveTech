#-------------------------------------------------
#
# Project created by QtCreator 2017-12-18T10:59:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TEMPLATE = app

LIBS_PATH=$${PWD}/../../Libs

INCLUDEPATH+=$${PWD}/src\
            $${PWD}/src/UI\
            $${PWD}/src/UI/IUiWidget\
            $${LIBS_PATH}/Com/Communication\
            $${LIBS_PATH}/GTUtils\
            $${LIBS_PATH}/GTUtils/QtTreeManager\


CONFIG(debug, debug|release){
    APPTEST_OUT_PATH=$${PWD}/../../build/debug/bin
    LIBPATH=$${APPTEST_OUT_PATH}
    LIBS +=-lCommunicationd\
          -lGTUtilsd
    TARGET = UiSrcAppd
} else{
    APPTEST_OUT_PATH=$${PWD}/../../build/release/bin
    LIBPATH=$${APPTEST_OUT_PATH}
#    LIBS +=$${APPTEST_OUT_PATH}\Communication.lib\
#           $${APPTEST_OUT_PATH}\GTUtils.lib
    LIBS +=-lCommunication\
          -lGTUtils
   TARGET = UiSrcApp
}
DESTDIR =$${APPTEST_OUT_PATH}


SOURCES += main.cpp\
        uisrcmainwindow.cpp \
    src/Kernel/axistreemap.cpp \
    src/Kernel/devcomrwriter.cpp \
    src/Kernel/deviceconfig.cpp \
    src/Kernel/devtextrwriter.cpp \
    src/Kernel/gconfigreadwriter.cpp \
    src/Kernel/globalconfig.cpp \
    src/Kernel/globaluicontroler.cpp \
    src/Kernel/ictrboard.cpp \
    src/Kernel/idevreadwriter.cpp \
    src/Kernel/idspmap.cpp \
    src/Kernel/ipwrboard.cpp \
    src/Kernel/iuicontroler.cpp \
    src/Kernel/linksocket.cpp \
    src/Kernel/sdassembly.cpp \
    src/Kernel/sevctrboard.cpp \
    src/Kernel/sevdevice.cpp \
    src/Kernel/sevdspmap.cpp \
    src/Kernel/sevpwrboard.cpp \
    src/Kernel/sevuicontroler.cpp \
    src/Kernel/PowerTreeManage/powertreemanage.cpp \
    src/UI/IUiWidget/iuiwidget.cpp \
    src/UI/UiBrake/uibrake.cpp \
    src/UI/UiCurrent/uicurrent.cpp \
    src/UI/UiEncoder/uiencoder.cpp \
    src/UI/UiFLASH/uiflash.cpp \
    src/UI/UiIO/uiio.cpp \
    src/UI/UiMotor/uimotor.cpp \
    src/UI/UiPlot/uiplot.cpp \
    src/UI/UiPosition/uiposition.cpp \
    src/UI/UiPower/uipower.cpp \
    src/UI/UiRAM/uiram.cpp \
    src/UI/UiStatus/uistatus.cpp \
    src/UI/UiVelocity/uivelocity.cpp \
    src/UiFactory/uifactory.cpp

HEADERS  += uisrcmainwindow.h \
    src/Kernel/axistreemap.h \
    src/Kernel/devcomrwriter.h \
    src/Kernel/deviceconfig.h \
    src/Kernel/devtextrwriter.h \
    src/Kernel/gconfigreadwriter.h \
    src/Kernel/globalconfig.h \
    src/Kernel/globaluicontroler.h \
    src/Kernel/ictrboard.h \
    src/Kernel/idevreadwriter.h \
    src/Kernel/idspmap.h \
    src/Kernel/ipwrboard.h \
    src/Kernel/iuicontroler.h \
    src/Kernel/linksocket.h \
    src/Kernel/sdassembly.h \
    src/Kernel/sevctrboard.h \
    src/Kernel/sevdevice.h \
    src/Kernel/sevdeviceprivate_p.h \
    src/Kernel/sevdspmap.h \
    src/Kernel/sevpwrboard.h \
    src/Kernel/sevuicontroler.h \
    src/Kernel/PowerTreeManage/powertreemanage.h \
    src/UI/IUiWidget/iuiwidget.h \
    src/UI/IUiWidget/iuiwidget_p.h \
    src/UI/IUiWidget/iuiwidgetgdef.h \
    src/UI/UiBrake/uibrake.h \
    src/UI/UiCurrent/uicurrent.h \
    src/UI/UiEncoder/uiencoder.h \
    src/UI/UiFLASH/uiflash.h \
    src/UI/UiIO/uiio.h \
    src/UI/UiMotor/uimotor.h \
    src/UI/UiPlot/uiplot.h \
    src/UI/UiPosition/uiposition.h \
    src/UI/UiPower/uipower.h \
    src/UI/UiRAM/uiram.h \
    src/UI/UiStatus/uistatus.h \
    src/UI/UiVelocity/uivelocity.h \
    src/UiFactory/registerfunction.h \
    src/UiFactory/uifactory.h

FORMS    += uisrcmainwindow.ui \
    src/UI/UiBrake/uibrake.ui \
    src/UI/UiCurrent/uicurrent.ui \
    src/UI/UiEncoder/uiencoder.ui \
    src/UI/UiFLASH/uiflash.ui \
    src/UI/UiIO/uiio.ui \
    src/UI/UiMotor/uimotor.ui \
    src/UI/UiPlot/uiplot.ui \
    src/UI/UiPosition/uiposition.ui \
    src/UI/UiPower/uipower.ui \
    src/UI/UiRAM/uiram.ui \
    src/UI/UiStatus/uistatus.ui \
    src/UI/UiVelocity/uivelocity.ui
