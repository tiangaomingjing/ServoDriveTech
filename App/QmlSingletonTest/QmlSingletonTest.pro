include(../App.pri)

TEMPLATE = app
CONFIG(debug, debug|release){
  TARGET = QmlSingletonTestd
#  DESTPATH=$${PWD}/../../build/debug/bin/
} else{
  TARGET = QmlSingletonTest
#  DESTPATH=$${PWD}/../../build/release/bin/
}

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    stylereshelper.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =$$PWD

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    stylereshelper.h

#target.path=$$DESTPATH
#qmldir.files=$$PWD/qmldir
#qmldir.path=$$DESTPATH
#INSTALLS+=target qmldir

#CONFIG+=install_ok
#cpqmldir.files=qmldir
#cpqmldir.path=$$DESTPATH
#COPIES+=cpqmldir

DISTFILES += \
    Resource/qmldir \
    Resource/StyleRes.qml
