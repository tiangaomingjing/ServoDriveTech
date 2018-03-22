#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T10:02:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += $${PWD}/../../Libs/GTUtils\
               $${PWD}/../../Libs/GTUtils/QtTreeManager\

CONFIG(debug, debug|release){
    TARGET = ComparisonDialogd
    LIB_PATH = $${PWD}/../../build/debug/Bin
    OUT_ROOT = $${PWD}/../../build/debug
    LIBS += $${LIB_PATH}/GTUtilsd.lib

} else{
    TARGET = ComparisonDialog
    LIB_PATH = $${PWD}/../../build/release/Bin
    OUT_ROOT = $${PWD}/../../build/release
    LIBS += $${LIB_PATH}/GTUtils.lib
}

DESTDIR =$${OUT_ROOT}/Bin

SOURCES += main.cpp\
        comparisondialog.cpp

HEADERS  += comparisondialog.h

FORMS    += comparisondialog.ui
