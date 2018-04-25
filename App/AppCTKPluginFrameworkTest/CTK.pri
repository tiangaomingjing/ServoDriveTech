CTK_PATH=$$PWD/../../Libs/ThirdParty/CTK
include($$CTK_PATH/CTKlibs.pri)

CONFIG(debug, debug|release){
  DESTDIR=$$PWD/../../build/debug/bin
} else{
  DESTDIR=$$PWD/../../build/release/bin
}

