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
  TARGET = CurveUsrIu
}else{
  TARGET = CurveUsrIu
}
DESTDIR=$$PLOT_PLUGINS_PATH/user

SOURCES += curveusriu.cpp \
    curveusriuactivator.cpp

HEADERS += curveusriu.h \
    curveusriuactivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
