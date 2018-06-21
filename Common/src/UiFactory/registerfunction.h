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

#include "UiBrake/graphbrake129.h"
#include "UiCurrent/graphcurrent129.h"
#include "UiEncoder/graphencoder129.h"
#include "UiMotor/graphmotor129.h"
#include "UiPosition/graphposition129.h"
#include "UiPower/graphpower129.h"
#include "UiStatus/graphstatus129.h"
#include "UiVelocity/graphvelocity129.h"

#include "UiCurrent/graphcurrent130.h"
#include "UiCurrent/graphcurrent133.h"
#include "UiPosition/graphposition133.h"

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

  UiFactory::registerClass<GraphBrake129>();
  UiFactory::registerClass<GraphCurrent129>();
  UiFactory::registerClass<GraphEncoder129>();
  UiFactory::registerClass<GraphMotor129>();
  UiFactory::registerClass<GraphPosition129>();
  UiFactory::registerClass<GraphPower129>();
  UiFactory::registerClass<GraphStatus129>();
  UiFactory::registerClass<GraphVelocity129>();

  UiFactory::registerClass<GraphCurrent130>();
  UiFactory::registerClass<GraphCurrent133>();
  UiFactory::registerClass<GraphPosition133>();
}

}

#endif // REGISTERFUNCTION

