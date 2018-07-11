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
  TARGET = CurveUsrIv
}else{
  TARGET = CurveUsrIv
}
DESTDIR=$$PLOT_PLUGINS_PATH/user

SOURCES += curveusriv.cpp \
    curveusrivactivator.cpp

HEADERS += curveusriv.h \
    curveusrivactivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
