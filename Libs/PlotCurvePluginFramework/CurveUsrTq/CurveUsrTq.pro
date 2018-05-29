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
  TARGET = CurveUsrTq
}else{
  TARGET = CurveUsrTq
}
DESTDIR=$$PLOT_PLUGINS_PATH/user

SOURCES += curveusrtq.cpp \
    curveusrtqactivator.cpp

HEADERS += curveusrtq.h \
    curveusrtqactivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
