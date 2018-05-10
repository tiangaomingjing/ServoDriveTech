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
  TARGET = CurveRaw
}else{
  TARGET = CurveRaw
}
DESTDIR=$$PLOT_PLUGINS_PATH/expert

SOURCES += curveraw.cpp \
    curverawactivator.cpp

HEADERS += curveraw.h \
    curverawactivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
