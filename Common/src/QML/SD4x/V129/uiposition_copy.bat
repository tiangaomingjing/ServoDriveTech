@echo off  			::close echo
@cls				::clean screen
@echo copy qmlfile target directory automatic		::display info
@echo author chenchao							::display info
@echo date:2018.01.16							::display info


@copy /y .\UiPosition.qml  ..\..\..\..\..\build\debug\sysconfig\SD4x\SD42\V129\ui
@copy /y .\UiPosition.qml  ..\..\..\..\..\build\release\sysconfig\SD4x\SD42\V129\ui