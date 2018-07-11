TEMPLATE = lib

DEFINES+=COM_SHARED_LIBRARY
include(../Com.pri)

INCLUDEPATH+=$${PWD}/../ServoDriverComDll/DllCom

CONFIG(debug, debug|release){
    LIBS +=$${COM_OUT_PATH}/ServoDriverComDlld.lib
    TARGET = Communicationd
} else{
    LIBS +=$${COM_OUT_PATH}/ServoDriverComDll.lib
    TARGET = Communication
}


SOURCES += \
    icom.cpp \
    pcdebug.cpp \
    rnnet.cpp

HEADERS += \
    icom.h \
    icom_p.h \
    comglobal.h \
    pcdebug.h \
    pcdebug_p.h \
    rnnet.h \
    rnnet_p.h


