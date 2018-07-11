QT += core widgets
QT -= gui


CONFIG += console
CONFIG -= app_bundle

DEFINES += ICURVE_LIBRARY

TEMPLATE = lib

INCLUDEPATH +=$$PWD/../../GTUtils

CONFIG(debug,debug|release){
  TARGET = ICurved
  BIN_PATH=$$PWD/../../../build/debug/bin
  LIBS +=$$BIN_PATH/GTUtilsd.lib
}else{
  TARGET = ICurve
  BIN_PATH=$$PWD/../../../build/release/bin
  LIBS +=$$BIN_PATH/GTUtils.lib
}

DESTDIR = $$BIN_PATH
SOURCES += \
    icurve.cpp

HEADERS += \
    icurve.h \
    icurve_global.h \
    icurvedef.h

