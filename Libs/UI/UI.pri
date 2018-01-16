include (../Libs.pri)
INCLUDEPATH+=$${PWD}/IUiWidget\
            $${PWD}/../SDKernel\
            $${PWD}/../Option

QT+=quickwidgets qml

CONFIG(debug, debug|release){
    UI_OUT_PATH = $${APP_BUILD_PATH}/debug/bin
    LIBS+=$${UI_OUT_PATH}/IUiWidgetd.lib\
          $${UI_OUT_PATH}/SDKerneld.lib\
          $${UI_OUT_PATH}/Optiond.lib
} else{
    UI_OUT_PATH = $${APP_BUILD_PATH}/release/bin
    LIBS+=$${UI_OUT_PATH}/IUiWidgetd.lib\
          $${UI_OUT_PATH}/SDKernel.lib\
          $${UI_OUT_PATH}/Option.lib
}
DESTDIR =$${UI_OUT_PATH}

QML_IMPORT_TRACE=1
