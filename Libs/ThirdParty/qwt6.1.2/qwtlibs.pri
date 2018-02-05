QWT_PATH =D:/program/Qt/QwtLibs
QWT_VERSION=VS2013

QWT_INCLUDE=$${QWT_PATH}/includes
QWT_LIBS=$${QWT_PATH}/$${QWT_VERSION}/libs
QWT_BIN=$${QWT_PATH}/$${QWT_VERSION}/bin
INCLUDEPATH+=QWT_INCLUDE

CONFIG(debug,debug|release){
LIBS+=$${QWT_LIBS}/qwtd.lib
}else{
LIBS+=$${QWT_LIBS}/qwt.lib
}
