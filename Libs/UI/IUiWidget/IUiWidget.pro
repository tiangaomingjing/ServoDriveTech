#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T10:15:43
#
#-------------------------------------------------

include (../../Libs.pri)
INCLUDEPATH+=$${PWD}/../../SDKernel\
              $${PWD}/../../GTUtils\
              $${PWD}/../../Option

QT       += widgets quickwidgets qml

QT       -= gui


TEMPLATE = lib

DEFINES += IUIWIDGET_LIBRARY

CONFIG(debug, debug|release){
    UI_OUT_PATH = $${APP_BUILD_PATH}/debug/bin
    LIBS+=$${UI_OUT_PATH}/SDKerneld.lib\
          $${UI_OUT_PATH}/GTUtilsd.lib\
          $${UI_OUT_PATH}/Optiond.lib
    TARGET = IUiWidgetd
} else{
    UI_OUT_PATH = $${APP_BUILD_PATH}/release/bin
    LIBS+=$${UI_OUT_PATH}/SDKernel.lib\
          $${UI_OUT_PATH}/GTUtils.lib\
          $${UI_OUT_PATH}/Option.lib
    TARGET = IUiWidget
}



DESTDIR =$${UI_OUT_PATH}


SOURCES += iuiwidget.cpp

HEADERS += iuiwidget.h\
        iuiwidget_global.h \
    iuiwidget_p.h \
    iuiwidgetgdef.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QML_IMPORT_TRACE=1
