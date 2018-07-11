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
  TARGET = CurveUsrVffd
}else{
  TARGET = CurveUsrVffd
}
DESTDIR=$$PLOT_PLUGINS_PATH/user

SOURCES += curveusrvffd.cpp \
    curveusrvffdactivator.cpp

HEADERS += curveusrvffd.h \
    curveusrvffdactivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
