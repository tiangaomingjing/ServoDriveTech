#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T10:15:43
#
#-------------------------------------------------

include (../../Libs.pri)
INCLUDEPATH+=$${PWD}/../../SDKernel\
              $${PWD}/../../GTUtils\
              $${PWD}/../../Option\
              $${PWD}/SDTGraphicsItems

QT       += widgets quickwidgets qml

QT       -= gui


TEMPLATE = lib

DEFINES += IUIWIDGET_LIBRARY \
           SDTGRAPHICSITEMS_LIBRARY

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


SOURCES += iuiwidget.cpp \
    igraphmotor.cpp \
    igraphencoder.cpp \
    igraphcurrent.cpp \
    igraphposition.cpp \
    igraphpower.cpp \
    igraphstatus.cpp \
    igraphvelocity.cpp \
    igraphwidget.cpp \
    imapping.cpp \
    boxitemmapping.cpp\
    igraph.cpp \
    igraphbrake.cpp \
    idatabinding.cpp \
    interactiveview.cpp \
    SDTGraphicsItems/anchoritemhelper.cpp \
    SDTGraphicsItems/arrowitem.cpp \
    SDTGraphicsItems/sumitemwidget.cpp \
    SDTGraphicsItems/targetitemwidget.cpp \
    SDTGraphicsItems/widgetitem.cpp \
    SDTGraphicsItems/labelitemwidget.cpp \
    SDTGraphicsItems/saturationitemwidget.cpp

HEADERS += iuiwidget.h\
        iuiwidget_global.h \
    iuiwidget_p.h \
    iuiwidgetgdef.h \
    igraphmotor.h \
    igraphencoder.h \
    igraphcurrent.h \
    igraphposition.h \
    igraphpower.h \
    igraphstatus.h \
    igraphvelocity.h \
    igraphcurrent_p.h \
    igraphencoder_p.h \
    igraphmotor_p.h \
    igraphposition_p.h \
    igraphpower_p.h \
    igraphstatus_p.h \
    igraphvelocity_p.h \
    igraphwidget.h \
    imapping.h \
    boxitemmapping.h\
    igraph.h \
    igraph_p.h \
    igraphbrake.h \
    igraphbrake_p.h \
    igraphwidget_p.h \
    idatabinding.h \
    interactiveview.h \
    SDTGraphicsItems/anchoritemhelper.h \
    SDTGraphicsItems/arrowitem.h \
    SDTGraphicsItems/sdtgraphicsitems_global.h \
    SDTGraphicsItems/sumitemwidget.h \
    SDTGraphicsItems/targetitemwidget.h \
    SDTGraphicsItems/widgetitem.h \
    SDTGraphicsItems/SDTGraphicsItems \
    SDTGraphicsItems/labelitemwidget.h \
    SDTGraphicsItems/saturationitemwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QML_IMPORT_TRACE=1
