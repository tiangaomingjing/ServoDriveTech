#-------------------------------------------------
#
# Project created by QtCreator 2017-11-28T19:42:06
#
#-------------------------------------------------

QT       += core gui designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

include(../Com.pri)


INCLUDEPATH+=$${PWD}/../Communication

CONFIG(debug, debug|release){
    LIBS +=$${COM_OUT_PATH}/Communicationd.lib
    TARGET = CommunicationTestd
} else{
    LIBS +=$${COM_OUT_PATH}/Communication.lib
    TARGET = CommunicationTest
}


SOURCES += main.cpp\
        comwindowtest.cpp \
    ../../../Common/QtTreeManager/qttreemanager.cpp

HEADERS  += comwindowtest.h \
    ../../../Common/QtTreeManager/qttreemanager.h

FORMS    += comwindowtest.ui
