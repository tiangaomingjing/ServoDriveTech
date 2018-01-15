#-------------------------------------------------
#
# Project created by QtCreator 2018-01-15T10:53:41
#
#-------------------------------------------------
include(../App.pri)

QT       += core gui qml quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TEMPLATE = app
CONFIG(debug, debug|release){
  TARGET = QmlStyleTestd
} else{
  TARGET = QmlStyleTest
}


SOURCES += main.cpp\
        qmlstylewindow.cpp \
    qmlstylehelper.cpp

HEADERS  += qmlstylewindow.h \
    qmlstylehelper.h

FORMS    += qmlstylewindow.ui

DISTFILES += \
    Qmlw1.qml \
    Qmlw2.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/BlackStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/blue/BlueStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/IStyle.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/blue/Qmlw1Style.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/blue/Qmlw2Style.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/StyleLoader.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/Qmlw1Style.qml \
    ../../build/debug/custom/option/qmlstyle/MyQmlStyle/black/Qmlw2Style.qml

QML_IMPORT_TRACE=1
QML_IMPORT_PATH =$${PWD}/../../build/debug/custom/option/qmlstyle
message($$QML_IMPORT_PATH)

