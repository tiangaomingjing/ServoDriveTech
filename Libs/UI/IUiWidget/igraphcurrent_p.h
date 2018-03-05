﻿#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphcurrent.h"
#include "igraphwidget_p.h"

class AnchorItemHelper;
class WidgetItem;
class ArrowItem;

class IUIWIDGETSHARED_EXPORT IGraphCurrentPrivate:public IGraphWidgetPrivate
{
  Q_DECLARE_PUBLIC(IGraphCurrent)
public:
  IGraphCurrentPrivate();
  virtual ~IGraphCurrentPrivate();
protected:
  AnchorItemHelper *m_anchorHelper;
  WidgetItem *m_Tstart;
  WidgetItem *m_Tend;
  WidgetItem *m_T0;

  WidgetItem *m_UPID;
  WidgetItem *m_USUM;
  WidgetItem *m_UIF;
  WidgetItem *m_UCB;

  ArrowItem *m_A0;
  ArrowItem *m_A1;
  ArrowItem *m_A2;
  ArrowItem *m_A3;
  ArrowItem *m_A4;
  ArrowItem *m_A5;

  QList<ArrowItem *>m_arrowList;
};

#endif // IGRAPHBRAKE_P_H

