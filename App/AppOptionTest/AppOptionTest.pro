#-------------------------------------------------
#
# Project created by QtCreator 2017-12-26T11:11:37
#
#-------------------------------------------------
include(../App.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG(debug, debug|release){
  TARGET = AppOptionTestd
} else{
  TARGET = AppOptionTest
}


SOURCES += main.cpp\
        optionmainwindow.cpp

HEADERS  += optionmainwindow.h

FORMS    += optionmainwindow.ui
