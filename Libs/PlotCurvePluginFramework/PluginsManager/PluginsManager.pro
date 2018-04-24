include (../ctkplugins.pri)
INCLUDEPATH +=$$PWD/../../GTUtils
QT += core widgets
QT -= gui


CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

CONFIG(debug,debug|release){
  BIN_PATH=$$PWD/../../../build/debug/bin
  LIBS+=$$BIN_PATH/GTUtilsd.lib
  TARGET = PluginsManagerd
}else{
  BIN_PATH=$$PWD/../../../build/release/bin
  LIBS+=$$BIN_PATH/GTUtils.lib
  TARGET = PluginsManager
}

DESTDIR = $$BIN_PATH

SOURCES += main.cpp \
    pluginsmanager.cpp

HEADERS += \
    pluginsmanager.h

