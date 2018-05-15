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
  TARGET = CurveUsrIcmd
}else{
  TARGET = CurveUsrIcmd
}
DESTDIR=$$PLOT_PLUGINS_PATH/user

SOURCES += curveusricmd.cpp \
    curveusricmdactivator.cpp

HEADERS += curveusricmd.h \
    curveusricmdactivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
