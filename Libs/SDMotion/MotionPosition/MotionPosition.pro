#-------------------------------------------------
#
# Project created by QtCreator 2018-06-21T15:08:17
#
#-------------------------------------------------
include(../Motion.pri)
QT       += widgets

QT       -= gui

TEMPLATE = lib
CONFIG(debug, debug|release){
    TARGET = MotionPosidtiond
} else{
    TARGET = MotionPosition
}

DEFINES += MOTIONPOSITION_LIBRARY

SOURCES += motionposition.cpp \
    uimotionposition.cpp \
    posplanmotion.cpp

HEADERS += motionposition.h\
        motionposition_global.h \
    uimotionposition.h \
    posplanmotion.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uimotionposition.ui
