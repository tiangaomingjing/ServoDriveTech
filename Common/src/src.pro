QT += core
QT -= gui

TARGET = src
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Utils/utils.cpp \
    Kernel/idevreadwriter.cpp \
    Kernel/linksocket.cpp \
    Kernel/ictrboard.cpp \
    Kernel/ipwrboard.cpp \
    Kernel/axistreemap.cpp \
    Kernel/idspmap.cpp \
    Kernel/sevdevice.cpp \
    Kernel/iuicontroler.cpp \
    Kernel/sevuicontroler.cpp \
    Kernel/sdassembly.cpp


HEADERS += \
    sdtglobaldef.h \
    Utils/utils.h \
    Kernel/idevreadwriter.h \
    Kernel/linksocket.h \
    Kernel/ictrboard.h \
    Kernel/ipwrboard.h \
    Kernel/axistreemap.h \
    Kernel/idspmap.h \
    Kernel/sevdevice.h \
    Kernel/iuicontroler.h \
    Kernel/sevuicontroler.h \
    Kernel/sdassembly.h



