#-------------------------------------------------
#
# Project created by QtCreator 2017-12-29T14:08:39
#
#-------------------------------------------------
include(../App.pri)

INCLUDEPATH+= $${PWD}/DialogOption\
              $${PWD}/ScreenStartup\
              $${PWD}/SdtStatusBar\
              $${PWD}/ConfigDialog\
              $${PWD}/VerMatching\
              $${PWD}/MessageServer\
              $${PWD}/StatusMonitor\
              $${PWD}/CombinedWindow\
              $${PWD}/DeviceInfoDialog\
              $${PWD}/DialogAdvUsr\
              $${PWD}/DownloadDialog\
              $${PWD}/UploadDialog\
              $${PWD}/ServoFile

QT       += core gui qml sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG(debug, debug|release){
  TARGET = AppSDTd
} else{
  TARGET = AppSDT
}

SOURCES += main.cpp\
        sdtmainwindow.cpp \
    DialogOption/dialogoption.cpp \
    ../../Common/src/Kernel/devcomrwriter.cpp \
    ../../Common/src/Kernel/deviceconfig.cpp \
    ../../Common/src/Kernel/devtextrwriter.cpp \
    ../../Common/src/Kernel/gconfigreadwriter.cpp \
    ../../Common/src/Kernel/globalconfig.cpp \
    ../../Common/src/Kernel/globaluicontroler.cpp \
    ../../Common/src/Kernel/idevreadwriter.cpp \
    ../../Common/src/Kernel/iuicontroler.cpp \
    ../../Common/src/Kernel/sdassembly.cpp \
    ../../Common/src/Kernel/sevuicontroler.cpp \
    ../../Common/src/UiFactory/uifactory.cpp \
    ScreenStartup/screenstartup.cpp \
    SdtStatusBar/sdtstatusbar.cpp \
    SdtStatusBar/statuserrdialog.cpp \
    ConfigDialog/configdialog.cpp \
    VerMatching/ivermatching.cpp \
    VerMatching/memeryvermatching.cpp \
    VerMatching/dbvermatching.cpp \
    ../../Common/src/SdtGlobal/sdtglobaldef.cpp \
    ../../Common/src/Kernel/sdterror.cpp \
    MessageServer/clientsocket.cpp \
    MessageServer/messageserver.cpp \
    StatusMonitor/statusmonitor.cpp \
    CombinedWindow/combinedwindow.cpp\
    DeviceInfoDialog/deviceinfodialog.cpp \
    DialogAdvUsr/dialogadvusr.cpp \
    DownloadDialog/downloaddialog.cpp \
    ServoFile/servofile.cpp \
    UploadDialog/uploaddialog.cpp \
    FirmwareFlashDialog/firmwareflashdialog.cpp\
    sdttreewidgetnav.cpp

HEADERS  += sdtmainwindow.h \
    appiconname.h \
    DialogOption/dialogoption.h \
    ../../Common/src/Kernel/devcomrwriter.h \
    ../../Common/src/Kernel/deviceconfig.h \
    ../../Common/src/Kernel/devtextrwriter.h \
    ../../Common/src/Kernel/gconfigreadwriter.h \
    ../../Common/src/Kernel/globalconfig.h \
    ../../Common/src/Kernel/globaluicontroler.h \
    ../../Common/src/Kernel/idevreadwriter.h \
    ../../Common/src/Kernel/iuicontroler.h \
    ../../Common/src/Kernel/sdassembly.h \
    ../../Common/src/Kernel/sevdeviceprivate_p.h \
    ../../Common/src/Kernel/sevuicontroler.h \
    ../../Common/src/UiFactory/registerfunction.h \
    ../../Common/src/UiFactory/uifactory.h \
    ScreenStartup/screenstartup.h \
    SdtStatusBar/sdtstatusbar.h \
    SdtStatusBar/statuserrdialog.h \
    ConfigDialog/configdialog.h \
    VerMatching/ivermatching.h \
    VerMatching/memeryvermatching.h \
    VerMatching/dbvermatching.h \
    ../../Common/src/SdtGlobal/sdtglobaldef.h \
    ../../Common/src/Kernel/sdterror.h \
    MessageServer/clientsocket.h \
    MessageServer/messageserver.h \
    StatusMonitor/statusmonitor.h \
    CombinedWindow/combinedwindow.h\
    DeviceInfoDialog/deviceinfodialog.h \
    DialogAdvUsr/dialogadvusr.h \
    DownloadDialog/downloaddialog.h \
    ServoFile/servofile.h \
    UploadDialog/uploaddialog.h \
    FirmwareFlashDialog/firmwareflashdialog.h\
    sdttreewidgetnav.h

FORMS    += sdtmainwindow.ui \
    DialogOption/dialogoption.ui \
    SdtStatusBar/sdtstatusbar.ui \
    SdtStatusBar/statuserrdialog.ui \
    ConfigDialog/configdialog.ui \
    CombinedWindow/combinedwindow.ui\
    DeviceInfoDialog/deviceinfodialog.ui \
    DialogAdvUsr/dialogadvusr.ui \
    DownloadDialog/downloaddialog.ui \
    UploadDialog/uploaddialog.ui \
    FirmwareFlashDialog/firmwareflashdialog.ui

TRANSLATIONS    += ch_main.ts en_main.ts


QML_IMPORT_TRACE=1
