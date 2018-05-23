#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T16:48:23
#
#-------------------------------------------------

QT       += widgets printsupport

QT       -= gui

TEMPLATE = lib

CONFIG(debug, debug|release){
    IPLOT_OUT_PATH=$${PWD}/../../../build/debug/bin/
    TARGET = IPlotUnitd
} else{
    IPLOT_OUT_PATH=$${PWD}/../../../build/release/bin/
    TARGET = IPlotUnit
}
DESTDIR =$${IPLOT_OUT_PATH}

DEFINES += IPLOTUNIT_LIBRARY \
           QCUSTOMPLOT_COMPILE_LIBRARY

SOURCES += iplotunit.cpp \
    qcustomplot.cpp

HEADERS += iplotunit.h\
        iplotunit_global.h \
    iplotunit_p.h \
    qcustomplot.h \
    imotion_p.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
