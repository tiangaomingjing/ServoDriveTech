#-------------------------------------------------
#
# Project created by QtCreator 2018-03-29T19:31:22
#
#-------------------------------------------------
QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppCustomPlotTest
TEMPLATE = app


SOURCES += main.cpp\
        customplotmainwindow.cpp \
    gtplot.cpp \
    qcustomplot.cpp \
    qcpitemhandletag.cpp \
    qcpitemmeasure.cpp

HEADERS  += customplotmainwindow.h \
    gtplot.h \
    qcustomplot.h \
    qcpitemhandletag.h \
    qcpitemmeasure.h

FORMS    += customplotmainwindow.ui
