INCLUDEPATH +=$$PWD/IMotion\
              $$PWD/MotionVelocity\
              $$PWD/MotionPosition\

LIBS_PATH = $$PWD/../../build/

CONFIG(debug, debug|release){
    MOTION_LIBS_PATH = $${LIBS_PATH}/debug/bin
    LIBS+=  $${MOTION_LIBS_PATH}/IMotiond.lib\
            $${MOTION_LIBS_PATH}/MotionVelocityd.lib\
            $${MOTION_LIBS_PATH}/MotionPositiond.lib\
} else{
    MOTION_LIBS_PATH = $${LIBS_PATH}/release/bin
    LIBS+=  $${MOTION_LIBS_PATH}/IMotion.lib\
            $${MOTION_LIBS_PATH}/MotionVelocity.lib\
            $${MOTION_LIBS_PATH}/MotionPosition.lib\
}
