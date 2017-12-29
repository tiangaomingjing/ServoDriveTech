#-------------------------------------------------
#
# Project created by QtCreator 2017-12-29T14:08:39
#
#-------------------------------------------------
include(../App.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG(debug, debug|release){
  TARGET = AppSDTd
} else{
  TARGET = AppSDT
}

SOURCES += main.cpp\
        sdtmainwindow.cpp

HEADERS  += sdtmainwindow.h \
    appiconname.h

FORMS    += sdtmainwindow.ui
