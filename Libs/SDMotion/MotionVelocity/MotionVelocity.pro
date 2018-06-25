#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T19:47:10
#
#-------------------------------------------------
include(../Motion.pri)
QT       -= gui

QT    +=widgets

TEMPLATE = lib
CONFIG(debug, debug|release){
    TARGET = MotionVelocityd
} else{
    TARGET = MotionVelocity
}

DEFINES += MOTIONVELOCITY_LIBRARY

SOURCES += motionvelocity.cpp \
    uimotionvelocity.cpp
#    vmotionthread.cpp \

HEADERS += motionvelocity.h\
        motionvelocity_global.h \
    uimotionvelocity.h \
#    vmotionthread.h \
    velplanmotion.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uimotionvelocity.ui
