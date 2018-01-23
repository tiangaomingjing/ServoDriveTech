@echo off  		
@cls				
@echo copy qmlfile target directory automatic		
@echo author chenchao							
@echo date:2018.01.16							

@echo ******************************
@echo  copy UiBrake.qml to target
call uibrake_copy.bat
@echo  copy UiCurrent.qml to target
call uicurrent_copy.bat
@echo  copy UiEncoder.qml to target
call uiencoder_copy.bat
@echo  copy UiMotor.qml to target
call uimotor_copy.bat
@echo  copy UiPosition.qml to target
call uiposition_copy.bat
@echo  copy UiPower.qml to target
call uipower_copy.bat
@echo  copy UiSpeed.qml to target
call uispeed_copy.bat
@echo  copy UiStatus.qml to target
call uistatus_copy.bat
@echo  copy UiVelocity.qml to target
call uivelocity_copy.bat

@echo  all copy  finish	!
@echo ******************************	
				
