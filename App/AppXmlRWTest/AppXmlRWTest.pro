#-------------------------------------------------
#
# Project created by QtCreator 2018-04-09T13:56:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += $${PWD}/../../Libs/Com/ServoDriverComDll/DllCom\
               $${PWD}/../../Libs/Com/ServoDriverComDll/NetCom/include\
               $${PWD}/../../Libs/Com/ServoDriverComDll\

CONFIG(debug, debug|release){
    TARGET = AppXmlRWTest_d
    LIB_PATH = $${PWD}/../../build/debug/Bin
    OUT_ROOT = $${PWD}/../../build/debug
    LIBS += $${LIB_PATH}/ServoDriverComDlld.lib\

} else{
    TARGET = AppXmlRWTest
    LIB_PATH = $${PWD}/../../build/release/Bin
    OUT_ROOT = $${PWD}/../../build/release
    LIBS += $${LIB_PATH}/ServoDriverComDll.lib

}

SOURCES += main.cpp\
        appxmlrwtest.cpp

HEADERS  += appxmlrwtest.h

FORMS    += appxmlrwtest.ui
