include(../Libs.pri)
INCLUDEPATH +=$$PWD/../GTUtils\
              $$PWD/../Option\
              $$PWD/../SDKernel\
              $$PWD/../Com/Communication\
              $$PWD/IMotion


CONFIG(debug, debug|release){
    MOTION_OUT_PATH = $${APP_BUILD_PATH}/debug/bin
    LIBS+=\
          $${MOTION_OUT_PATH}/GTUtilsd.lib\
          $${MOTION_OUT_PATH}/Optiond.lib\
          $${MOTION_OUT_PATH}/IMotiond.lib\
          $${MOTION_OUT_PATH}/SDKerneld.lib
} else{
    MOTION_OUT_PATH = $${APP_BUILD_PATH}/release/bin
    LIBS+=\
          $${MOTION_OUT_PATH}/GTUtils.lib\
          $${MOTION_OUT_PATH}/Option.lib\
          $${MOTION_OUT_PATH}/IMotion.lib\
          $${MOTION_OUT_PATH}/SDKernel.lib
}
DESTDIR =$${MOTION_OUT_PATH}
