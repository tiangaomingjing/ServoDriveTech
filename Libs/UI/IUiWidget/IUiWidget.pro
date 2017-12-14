#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T10:15:43
#
#-------------------------------------------------

include (../../Libs.pri)

QT       += widgets

QT       -= gui


TEMPLATE = lib

DEFINES += IUIWIDGET_LIBRARY

CONFIG(debug, debug|release){
    UI_OUT_PATH = $${APP_BUILD_PATH}/debug/bin
    TARGET = IUiWidgetd
} else{
    UI_OUT_PATH = $${APP_BUILD_PATH}/release/bin
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


