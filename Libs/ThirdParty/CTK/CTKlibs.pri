CTK_LIBS=$${PWD}/lib/ctk-0.1
INCLUDEPATH+=$${PWD}/include/ctk-0.1

CONFIG(debug,debug|release){
	LIBS+=-L$${CTK_LIBS} -lCTKCore -lCTKPluginFramework
}else{
	LIBS+=-L$${CTK_LIBS} -lCTKCore -lCTKPluginFramework
}
