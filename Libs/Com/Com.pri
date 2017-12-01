include(../Libs.pri)
ComTest=0
isEqual(ComTest,1){
  BUILD_PATH=$${PWD}/build/
}
isEqual(ComTest,0){
  BUILD_PATH=$${APP_BUILD_PATH}
}

CONFIG(debug, debug|release){
    COM_OUT_PATH = $${BUILD_PATH}/debug/bin
} else{
    COM_OUT_PATH = $${BUILD_PATH}/release/bin
}
DESTDIR =$${COM_OUT_PATH}
