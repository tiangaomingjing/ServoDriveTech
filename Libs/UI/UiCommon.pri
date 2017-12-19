INCLUDEPATH+=$${PWD}/../GTUtils\
              $${PWD}/../GTUtils/QtTreeManager\
              $${PWD}/../Com/Communication
include (../Libs.pri)

CONFIG(debug, debug|release){
    UICOMMON_LIB_PATH = $${APP_BUILD_PATH}/debug/bin
    LIBS+=$${UICOMMON_LIB_PATH}/GTUtilsd.lib
} else{
    UICOMMON_LIB_PATH = $${APP_BUILD_PATH}/release/bin
    LIBS+=$${UICOMMON_LIB_PATH}/GTUtils.lib
}
