#ifndef IPLOTUNIT_P
#define IPLOTUNIT_P

#include "iplotunit.h"
class UiPlot;

class IPlotUnitPrivate
{
  Q_DECLARE_PUBLIC(IPlotUnit)
public:
  IPlotUnitPrivate():m_winIsIn(true)
  {

  }
  ~IPlotUnitPrivate()
  {

  }
protected:
  IPlotUnit *q_ptr;

  bool m_winIsIn;
  UiPlot *m_uiPlot;

};

#endif // IPLOTUNIT_P

