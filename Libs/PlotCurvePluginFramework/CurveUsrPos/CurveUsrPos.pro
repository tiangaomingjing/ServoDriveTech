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
  TARGET = CurveUsrPos
}else{
  TARGET = CurveUsrPos
}
DESTDIR=$$PLOT_PLUGINS_PATH/user

SOURCES += curveusrpos.cpp \
    curveusrposactivator.cpp

HEADERS += curveusrpos.h \
    curveusrposactivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
