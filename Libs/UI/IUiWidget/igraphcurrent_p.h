#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphcurrent.h"
#include "igraphwidget_p.h"

class IUIWIDGETSHARED_EXPORT IGraphCurrentPrivate:public IGraphWidgetPrivate
{
  Q_DECLARE_PUBLIC(IGraphCurrent)
public:
  IGraphCurrentPrivate();
  virtual ~IGraphCurrentPrivate();
protected:

};

#endif // IGRAPHBRAKE_P_H

