#ifndef IPLOTUNIT_P
#define IPLOTUNIT_P

#include "iplotunit.h"
class UiPlot;
class SevDevice;

class IPlotUnitPrivate
{
  Q_DECLARE_PUBLIC(IPlotUnit)
public:
  IPlotUnitPrivate():m_winIsIn(true),
    m_isActiving(false),
    m_curSevInx(0)
  {

  }
  virtual ~IPlotUnitPrivate()
  {

  }
protected:
  IPlotUnit *q_ptr;

  bool m_winIsIn;
  bool m_isActiving;
  UiPlot *m_uiPlot;
  QList<SevDevice *> m_sevList;
  quint8 m_curSevInx;

};

#endif // IPLOTUNIT_P

