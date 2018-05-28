#-------------------------------------------------
#
# Project created by QtCreator 2017-12-08T13:54:40
#
#-------------------------------------------------
include (../UI.pri)
QWT=$${PWD}/../../ThirdParty/qwt6.1.2
INCLUDEPATH+=$${QWT}/includes\
             $${PWD}/EncConfig

QT       += widgets

QT       -= gui

TARGET = UiEncoder
TEMPLATE = lib

DEFINES += UIENCODER_LIBRARY

CONFIG(debug, debug|release){
    LIBS+=$${QWT}/libs/qwtd.lib
    TARGET = UiEncoderd
} else{
    LIBS+=$${QWT}/libs/qwt.lib
    TARGET = UiEncoder
}

SOURCES += uiencoder.cpp \
    graphencoder129.cpp \
    ./EncConfig/encconfigmanage.cpp \
    ./EncConfig/iencconfigitem.cpp \
    EncConfig/encconfigduomoitem.cpp \
    EncConfig/encconfighaidehanitem.cpp \
    EncConfig/encconfignikangitem.cpp \
    EncConfig/encconfigsanxieitem.cpp \
    EncConfig/encconfigsongxiaitem.cpp \
    EncConfig/encconfigyaskawaitem.cpp \
    linenumberbinding.cpp \
    encconfigbinding129.cpp

HEADERS += uiencoder.h\
        uiencoder_global.h \
    graphencoder129.h \
    ./EncConfig/encconfigmanage.h \
    ./EncConfig/iencconfigitem.h \
    EncConfig/encconfigduomoitem.h \
    EncConfig/encconfighaidehanitem.h \
    EncConfig/encconfignikangitem.h \
    EncConfig/encconfigsanxieitem.h \
    EncConfig/encconfigsongxiaitem.h \
    EncConfig/encconfigyaskawaitem.h \
    EncConfig/EncConfig \
    linenumberbinding.h \
    encconfigbinding129.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    uiencoder.ui \
    graphencoder129.ui

TRANSLATIONS    += ch_uiencoder.ts en_uiencoder.ts
