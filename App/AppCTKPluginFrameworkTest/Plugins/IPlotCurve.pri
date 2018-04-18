INCLUDEPATH +=$$PWD/IPlotCurve

CTK_PATH=$$PWD/../../../Libs/ThirdParty/CTK
include($$CTK_PATH/CTKlibs.pri)

CONFIG(debug, debug|release){
  DESTDIR=$$PWD/../../../build/debug/bin/plugins/test
} else{
  DESTDIR=$$PWD/../../../build/release/bin/plugins/test
}
