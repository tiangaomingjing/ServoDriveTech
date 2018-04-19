#-------------------------------------------------
#
# Project created by QtCreator 2018-04-19T15:27:53
#
#-------------------------------------------------
include (../ctkplugins.pri)
QT       -= gui
QT+=widgets


TEMPLATE = lib

CONFIG(debug,debug|release){
  TARGET = CurveRawd
}else{
  TARGET = CurveRaw
}
DESTDIR=$$PLOT_PLUGINS_PATH/expert

SOURCES += curveraw.cpp \
    ../ICurve/icurve.cpp

HEADERS += curveraw.h \
    ../ICurve/icurve.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
