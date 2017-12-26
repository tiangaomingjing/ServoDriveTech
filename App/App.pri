LIBS_PATH=$${PWD}/../Libs
COMMON_PATH=$${PWD}/../Common

INCLUDEPATH+=$${LIBS_PATH}/Com/Communication\
            $${LIBS_PATH}/GTUtils\
            $${LIBS_PATH}/GTUtils/QtTreeManager\
            $${LIBS_PATH}/SDKernel\
            $${LIBS_PATH}/UI\
            $${LIBS_PATH}/UI/IUiWidget\
            $${LIBS_PATH}/Option\
            $${COMMON_PATH}/src


CONFIG(debug, debug|release){
    APPTEST_OUT_PATH=$${PWD}/../build/debug/bin
    LIBPATH=$${APPTEST_OUT_PATH}
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
          -lOptiond
} else{
    APPTEST_OUT_PATH=$${PWD}/../build/release/bin
    LIBPATH=$${APPTEST_OUT_PATH}
#    LIBS +=$${APPTEST_OUT_PATH}\Communication.lib\
#           $${APPTEST_OUT_PATH}\GTUtils.lib
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
          -lOption
}
DESTDIR =$${APPTEST_OUT_PATH}
