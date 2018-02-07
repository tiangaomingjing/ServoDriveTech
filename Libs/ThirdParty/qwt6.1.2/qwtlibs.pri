QWT_LIBS=$${PWD}/libs
INCLUDEPATH+=$${PWD}/includes

CONFIG(debug,debug|release){
LIBS+=$${QWT_LIBS}/qwtd.lib
}else{
LIBS+=$${QWT_LIBS}/qwt.lib
}
