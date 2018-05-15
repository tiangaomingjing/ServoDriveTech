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
  TARGET = CurveUsrIfb
}else{
  TARGET = CurveUsrIfb
}
DESTDIR=$$PLOT_PLUGINS_PATH/user

SOURCES += curveusrifb.cpp \
    curveusrifbactivator.cpp

HEADERS += curveusrifb.h \
    curveusrifbactivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
