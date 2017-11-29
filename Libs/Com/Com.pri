BUILD_PATH=$${PWD}/build

CONFIG(debug, debug|release){
    COM_OUT_PATH = $${BUILD_PATH}/debug/bin
} else{
    COM_OUT_PATH = $${BUILD_PATH}/release/bin
}
DESTDIR =$${COM_OUT_PATH}
