#-------------------------------------------------
#
# Project created by QtCreator 2018-04-18T11:39:02
#
#-------------------------------------------------
include($$PWD/../IPlotCurve.pri)

QT       -= gui

TEMPLATE = lib

CONFIG(debug,debug|release){
  TARGET = PlotCurveUsrPosd
}else{
  TARGET = PlotCurveUsrPos
}

SOURCES += \
    ../IPlotCurve/iplotcurve.cpp \
    plotcurveusrpos.cpp \
    plotcurveusrposactivator.cpp

HEADERS += \
    ../IPlotCurve/iplotcurve.h \
    plotcurveusrpos.h \
    plotcurveusrposactivator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
