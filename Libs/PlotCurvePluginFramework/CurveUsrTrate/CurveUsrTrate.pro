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
  TARGET = CurveUsrTrate
}else{
  TARGET = CurveUsrTrate
}
DESTDIR=$$PLOT_PLUGINS_PATH/user

SOURCES += curveusrtrate.cpp \
    curveusrtrateactivator.cpp

HEADERS += curveusrtrate.h \
    curveusrtrateactivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
