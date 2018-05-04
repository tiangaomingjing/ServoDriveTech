#ifndef PLOTDATA
#define PLOTDATA
#include <QHash>
#include "icurvedef.h"
class ICurve;
class PlotData
{
public:
  QHash<ICurve*,CurveData> m_dataHash;
};

#endif // PLOTDATA

