INCLUDEPATH +=$$PWD/ICurve\
              $$PWD/../ThirdParty/CTK/include/ctk-0.1

CTK_LIB_PATH=$$PWD/../ThirdParty/CTK/lib/ctk-0.1
BUILD_PATH=$$PWD/../../build


CONFIG(debug,debug|release){
  LIBS+=$$CTK_LIB_PATH/CTKCore.lib\
        $$CTK_LIB_PATH/CTKPluginFramework.lib\
        $$BUILD_PATH/debug/bin/ICurved.lib
  PLOT_PLUGINS_PATH=$$PWD/../../build/debug/custom/plugins/plot
}else{
  LIBS+=$$CTK_LIB_PATH/CTKCore.lib\
        $$CTK_LIB_PATH/CTKPluginFramework.lib\
        $$BUILD_PATH/debug/bin/ICurve.lib
  PLOT_PLUGINS_PATH=$$PWD/../../build/release/custom/plugins/plot
}
