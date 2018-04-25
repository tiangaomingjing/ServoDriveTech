#-------------------------------------------------
#
# Project created by QtCreator 2018-04-18T11:39:02
#
#-------------------------------------------------
include($$PWD/../IPlotCurve.pri)

QT       -= gui

TEMPLATE = lib

CONFIG(debug,debug|release){
  TARGET = PlotCurveRawd
}else{
  TARGET = PlotCurveRaw
}

SOURCES += plotcurveraw.cpp \
    plotcurverawactivator.cpp \
    ../IPlotCurve/iplotcurve.cpp

HEADERS += plotcurveraw.h \
    plotcurverawactivator.h \
    ../IPlotCurve/iplotcurve.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
