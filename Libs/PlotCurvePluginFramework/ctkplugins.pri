INCLUDEPATH +=$$PWD/ICurve\
              $$PWD/../ThirdParty/CTK/include/ctk-0.1

CTK_LIB_PATH=$$PWD/../ThirdParty/CTK/lib/ctk-0.1


CONFIG(debug,debug|release){
  LIBS+=-L$$CTK_LIB_PATH -lCTKCore -lCTKPluginFramework
  PLOT_PLUGINS_PATH=$$PWD/../../build/debug/custom/plugins/plot
}else{
  LIBS+=-L$$CTK_LIB_PATH -lCTKCore -lCTKPluginFramework
  PLOT_PLUGINS_PATH=$$PWD/../../build/release/custom/plugins/plot
}
