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
        optionmainwindow.cpp \
    dialogoption.cpp \
    formlangtest1.cpp \
    formlangtest2.cpp

HEADERS  += optionmainwindow.h \
    dialogoption.h \
    formlangtest1.h \
    formlangtest2.h

FORMS    += optionmainwindow.ui \
    dialogoption.ui \
    formlangtest1.ui \
    formlangtest2.ui

TRANSLATIONS    += ch_main_test.ts en_main_test.ts
