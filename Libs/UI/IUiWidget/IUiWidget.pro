#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T10:15:43
#
#-------------------------------------------------

include (../../Libs.pri)
INCLUDEPATH+=$${PWD}/../../SDKernel\
              $${PWD}/../../GTUtils\
              $${PWD}/../../Com/Communication\
              $${PWD}/../../GTUtils/QtTreeManager\
              $${PWD}/../../Option\
              $${PWD}/../../AdvUser\
              $${PWD}/SDTGraphicsItems\
              $${PWD}/DataBinding\
              $${PWD}/nodeitem

QT       += widgets quickwidgets qml

QT       -= gui


TEMPLATE = lib

DEFINES += IUIWIDGET_LIBRARY \
           SDTGRAPHICSITEMS_LIBRARY

CONFIG(debug, debug|release){
    UI_OUT_PATH = $${APP_BUILD_PATH}/debug/bin
    LIBS+=$${UI_OUT_PATH}/SDKerneld.lib\
          $${UI_OUT_PATH}/GTUtilsd.lib\
          $${UI_OUT_PATH}/Optiond.lib\
          $${UI_OUT_PATH}/AdvUserd.lib
    TARGET = IUiWidgetd
} else{
    UI_OUT_PATH = $${APP_BUILD_PATH}/release/bin
    LIBS+=$${UI_OUT_PATH}/SDKernel.lib\
          $${UI_OUT_PATH}/GTUtils.lib\
          $${UI_OUT_PATH}/Option.lib\
          $${UI_OUT_PATH}/AdvUser.lib
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
    igraph.cpp \
    igraphbrake.cpp \
    interactiveview.cpp \
    SDTGraphicsItems/anchoritemhelper.cpp \
    SDTGraphicsItems/arrowitem.cpp \
    SDTGraphicsItems/sumitemwidget.cpp \
    SDTGraphicsItems/targetitemwidget.cpp \
    SDTGraphicsItems/widgetitem.cpp \
    SDTGraphicsItems/labelitemwidget.cpp \
    SDTGraphicsItems/saturationitemwidget.cpp \
    SDTGraphicsItems/frameitemwidget.cpp \
    ../../../Common/src/ledalarm.cpp \
    DataBinding/idatabinding.cpp \
    DataBinding/labelbinding.cpp \
    DataBinding/boxitemmapping.cpp \
    nodeitem/inodeconnection.cpp \
    nodeitem/nodeblock.cpp \
    nodeitem/nodecornerline.cpp \
    nodeitem/nodeline.cpp \
    nodeitem/nodeport.cpp \
    nodeitem/nodequadline.cpp \
    nodeitem/nodeswitch.cpp \
    IIRFilter/iirfilter.cpp

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
    igraph.h \
    igraph_p.h \
    igraphbrake.h \
    igraphbrake_p.h \
    igraphwidget_p.h \
    interactiveview.h \
    SDTGraphicsItems/anchoritemhelper.h \
    SDTGraphicsItems/arrowitem.h \
    SDTGraphicsItems/sdtgraphicsitems_global.h \
    SDTGraphicsItems/sumitemwidget.h \
    SDTGraphicsItems/targetitemwidget.h \
    SDTGraphicsItems/widgetitem.h \
    SDTGraphicsItems/SDTGraphicsItems \
    SDTGraphicsItems/labelitemwidget.h \
    SDTGraphicsItems/saturationitemwidget.h \
    SDTGraphicsItems/frameitemwidget.h \
    ../../../Common/src/ledalarm.h \
    DataBinding/idatabinding.h \
    DataBinding/labelbinding.h \
    DataBinding/boxitemmapping.h \
    nodeitem/inodeconnection.h \
    nodeitem/nodeblock.h \
    nodeitem/nodecornerline.h \
    nodeitem/nodeitemglobaldef.h \
    nodeitem/nodeline.h \
    nodeitem/nodeport.h \
    nodeitem/nodequadline.h \
    nodeitem/nodeswitch.h\
    nodeitem/NodeItems.h \
    IIRFilter/iirfilter.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QML_IMPORT_TRACE=1

TRANSLATIONS    += ch_uiwidget.ts en_uiwidget.ts

FORMS += \
    IIRFilter/iirfilter.ui


