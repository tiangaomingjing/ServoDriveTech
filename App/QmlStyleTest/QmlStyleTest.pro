#-------------------------------------------------
#
# Project created by QtCreator 2018-01-15T10:53:41
#
#-------------------------------------------------
include(../App.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TEMPLATE = app
CONFIG(debug, debug|release){
  TARGET = QmlStyleTestd
} else{
  TARGET = QmlStyleTest
}


SOURCES += main.cpp\
        qmlstylewindow.cpp \
    qmlstylehelper.cpp

HEADERS  += qmlstylewindow.h \
    qmlstylehelper.h

FORMS    += qmlstylewindow.ui
