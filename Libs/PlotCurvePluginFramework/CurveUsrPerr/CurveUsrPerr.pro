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
  TARGET = CurveUsrPerr
}else{
  TARGET = CurveUsrPerr
}
DESTDIR=$$PLOT_PLUGINS_PATH/user

SOURCES += curveusrperr.cpp \
    curveusrperractivator.cpp

HEADERS += curveusrperr.h \
    curveusrperractivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
