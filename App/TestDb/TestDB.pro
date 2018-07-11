#-------------------------------------------------
#
# Project created by QtCreator 2017-12-26T11:56:18
#
#-------------------------------------------------

QT       += core gui sql designer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += $${PWD}/dbManager\
               $${PWD}/../../Libs/Com/ServoDriverComDll/DllCom\
               $${PWD}/TreeManage\
               $${PWD}/Eprom\

CONFIG(debug, debug|release){
    TARGET = TestDb_d
    LIB_PATH = $${PWD}/../../build/debug/Bin
    OUT_ROOT = $${PWD}/../../build/debug
    LIBS += $${LIB_PATH}/ServoDriverComDlld.lib

} else{
    TARGET = TestDb
    LIB_PATH = $${PWD}/../../build/release/Bin
    OUT_ROOT = $${PWD}/../../build/release
    LIBS += $${LIB_PATH}/ServoDriverComDll.lib
}

DESTDIR =$${OUT_ROOT}/Bin

SOURCES += main.cpp\
        mainwindow.cpp \
    dbManager/dbmanager.cpp \
    tabletest.cpp \
    Eprom/eprom.cpp \
    Eprom/eprom_control.cpp \
    Eprom/eprom_power.cpp \
    TreeManage/treemanager.cpp \
    globaldefine.cpp

HEADERS  += mainwindow.h \
    dbManager/dbmanager.h \
    tabletest.h \
    globaldefine.h \
    Eprom/eprom.h \
    Eprom/eprom_control.h \
    Eprom/eprom_power.h \
    TreeManage/treemanager.h

FORMS    += mainwindow.ui \
    tabletest.ui
