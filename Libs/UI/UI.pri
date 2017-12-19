include (../Libs.pri)
INCLUDEPATH+=$${PWD}/IUiWidget\
            $${PWD}/../SDKernel
QT+=quickwidgets qml

CONFIG(debug, debug|release){
    UI_OUT_PATH = $${APP_BUILD_PATH}/debug/bin
    LIBS+=$${UI_OUT_PATH}/IUiWidgetd.lib\
          $${UI_OUT_PATH}/SDKerneld.lib
} else{
    UI_OUT_PATH = $${APP_BUILD_PATH}/release/bin
    LIBS+=$${UI_OUT_PATH}/IUiWidgetd.lib\
          $${UI_OUT_PATH}/SDKernel.lib
}
DESTDIR =$${UI_OUT_PATH}
