include(../Libs.pri)
INCLUDEPATH +=$$PWD/../GTUtils\
              $$PWD/../Option\


CONFIG(debug, debug|release){
    MOTION_OUT_PATH = $${APP_BUILD_PATH}/debug/bin
    LIBS+=\
          $${MOTION_OUT_PATH}/GTUtilsd.lib\
          $${MOTION_OUT_PATH}/Optiond.lib
} else{
    MOTION_OUT_PATH = $${APP_BUILD_PATH}/release/bin
    LIBS+=\
          $${MOTION_OUT_PATH}/GTUtils.lib\
          $${MOTION_OUT_PATH}/Option.lib
}
DESTDIR =$${MOTION_OUT_PATH}
