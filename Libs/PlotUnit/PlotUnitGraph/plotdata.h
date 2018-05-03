#ifndef PLOTDATA
#define PLOTDATA
#include <QHash>
#include <icurve.h>
class PlotData
{
public:
  QHash<ICurve*,CurveData> m_dataHash;
};

#endif // PLOTDATA

