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
  TARGET = CurveUsrVcmd
}else{
  TARGET = CurveUsrVcmd
}
DESTDIR=$$PLOT_PLUGINS_PATH/user

SOURCES += curveusrvcmd.cpp \
    curveusrvcmdactivator.cpp

HEADERS += curveusrvcmd.h \
    curveusrvcmdactivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
