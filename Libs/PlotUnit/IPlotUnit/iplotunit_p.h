#ifndef IPLOTUNIT_P
#define IPLOTUNIT_P

#include "iplotunit.h"
class UiPlot;

class IPlotUnitPrivate
{
  Q_DECLARE_PUBLIC(IPlotUnit)
public:
  IPlotUnitPrivate():m_winIsFloat(false)
  {

  }
  ~IPlotUnitPrivate()
  {

  }
protected:
  IPlotUnit *q_ptr;

  bool m_winIsFloat;
  UiPlot *m_uiPlot;

};

#endif // IPLOTUNIT_P

