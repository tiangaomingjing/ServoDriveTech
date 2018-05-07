QT += core widgets
QT -= gui


CONFIG += console
CONFIG -= app_bundle

DEFINES += ICURVE_LIBRARY

TEMPLATE = lib

CONFIG(debug,debug|release){
  TARGET = ICurved
  BIN_PATH=$$PWD/../../../build/debug/bin
}else{
  TARGET = ICurve
  BIN_PATH=$$PWD/../../../build/release/bin
}

DESTDIR = $$BIN_PATH
SOURCES += \
    icurve.cpp

HEADERS += \
    icurve.h \
    icurve_global.h \
    icurvedef.h

