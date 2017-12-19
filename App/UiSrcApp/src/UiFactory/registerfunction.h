#ifndef REGISTERFUNCTION
#define REGISTERFUNCTION
#include "UiBrake/uibrake.h"
#include "UiCurrent/uicurrent.h"
#include "UiEncoder/uiencoder.h"
#include "UiFLASH/uiflash.h"
#include "UiIO/uiio.h"
#include "UiMotor/uimotor.h"
#include "UiPlot/uiplot.h"
#include "UiPosition/uiposition.h"
#include "UiPower/uipower.h"
#include "UiRAM/uiram.h"
#include "UiStatus/uistatus.h"
#include "UiVelocity/uivelocity.h"
#include "UiFactory/uifactory.h"
namespace RegisterFunction {
void registerUiClass(){
  UiFactory::registerClass<UiBrake>();
  UiFactory::registerClass<UiCurrent>();
  UiFactory::registerClass<UiEncoder>();
  UiFactory::registerClass<UiFLASH>();
  UiFactory::registerClass<UiIO>();
  UiFactory::registerClass<UiMotor>();
  UiFactory::registerClass<UiPlot>();
  UiFactory::registerClass<UiPosition>();
  UiFactory::registerClass<UiPower>();
  UiFactory::registerClass<UiRAM>();
  UiFactory::registerClass<UiStatus>();
  UiFactory::registerClass<UiVelocity>();
}

}

#endif // REGISTERFUNCTION

