LIBS_PATH=$${PWD}/../Libs
COMMON_PATH=$${PWD}/../Common

INCLUDEPATH+=$${LIBS_PATH}/Com/Communication\
            $${LIBS_PATH}/GTUtils\
            $${LIBS_PATH}/GTUtils/QtTreeManager\
            $${LIBS_PATH}/GTUtils/DeviceIdHelper\
            $${LIBS_PATH}/GTUtils/SelfBuilder\
            $${LIBS_PATH}/SDKernel\
            $${LIBS_PATH}/AdvUser\
            $${LIBS_PATH}/UI\
            $${LIBS_PATH}/UI/UiPlot\
            $${LIBS_PATH}/UI/IUiWidget\
            $${LIBS_PATH}/Option\
            $${LIBS_PATH}/PlotUnit/PlotUnitGraph\
            $${LIBS_PATH}/PlotUnit/IPlotUnit\
            $${LIBS_PATH}/PlotCurvePluginFramework/ICurve\
            $${COMMON_PATH}/src\
            $${COMMON_PATH}/src/Kernel\
            $${COMMON_PATH}/src/UiFactory\
            $${COMMON_PATH}/src/SdtGlobal


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
          -lOptiond\
          -lPlotUnitGraphd\
          -lIPlotUnitd\
          -lAdvUserd
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
          -lOption\
          -lPlotUnitGraph\
          -lIPlotUnit\
          -lAdvUser
}
DESTDIR =$${APPTEST_OUT_PATH}
