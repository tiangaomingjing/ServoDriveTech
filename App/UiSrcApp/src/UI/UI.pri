include (../Libs.pri)
INCLUDEPATH+=$${PWD}/IUiWidget

CONFIG(debug, debug|release){
    UI_OUT_PATH = $${APP_BUILD_PATH}/debug/bin
    LIBS+=$${UI_OUT_PATH}/IUiWidgetd.lib
} else{
    UI_OUT_PATH = $${APP_BUILD_PATH}/release/bin
    LIBS+=$${UI_OUT_PATH}/IUiWidgetd.lib
}
DESTDIR =$${UI_OUT_PATH}
