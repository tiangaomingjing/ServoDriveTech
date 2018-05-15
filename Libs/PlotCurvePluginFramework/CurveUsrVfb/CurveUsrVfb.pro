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
  TARGET = CurveUsrVfb
}else{
  TARGET = CurveUsrVfb
}
DESTDIR=$$PLOT_PLUGINS_PATH/user

SOURCES += curveusrvfb.cpp \
    curveusrvfbactivator.cpp

HEADERS += curveusrvfb.h \
    curveusrvfbactivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
