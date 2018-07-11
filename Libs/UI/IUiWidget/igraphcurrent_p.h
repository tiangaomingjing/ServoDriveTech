#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphcurrent.h"
#include "igraphwidget_p.h"
#include "iuiwidget_global.h"

class AnchorItemHelper;
class WidgetItem;
class ArrowItem;
class QDoubleSpinBox;

class IUIWIDGETSHARED_EXPORT IGraphCurrentPrivate:public IGraphWidgetPrivate
{
  Q_DECLARE_PUBLIC(IGraphCurrent)
public:
  IGraphCurrentPrivate():IGraphWidgetPrivate(),
    m_anchorHelper(NULL),
    m_Tstart(NULL),
    m_Tend(NULL),
    m_T0(NULL),

    m_UPID(NULL),
    m_USUM(NULL),
    m_UIF(NULL),
    m_UCB(NULL),
    m_TextStart(NULL),
    m_TextEnd(NULL),

    m_A0(NULL),
    m_A1(NULL),
    m_A2(NULL),
    m_A3(NULL),
    m_A4(NULL),
    m_A5(NULL),

    m_pEdit(NULL),
    m_iEdit(NULL)
  {

  }
  virtual ~IGraphCurrentPrivate()
  {

  }

protected:
  AnchorItemHelper *m_anchorHelper;
  WidgetItem *m_Tstart;
  WidgetItem *m_Tend;
  WidgetItem *m_T0;

  WidgetItem *m_UPID;
  WidgetItem *m_USUM;
  WidgetItem *m_UIF;
  WidgetItem *m_UCB;

  WidgetItem *m_TextStart;
  WidgetItem *m_TextEnd;

  ArrowItem *m_A0;
  ArrowItem *m_A1;
  ArrowItem *m_A2;
  ArrowItem *m_A3;
  ArrowItem *m_A4;
  ArrowItem *m_A5;


  QList<ArrowItem *>m_arrowList;
  QList<WidgetItem *>m_widgetItemList;

  QDoubleSpinBox *m_pEdit;
  QDoubleSpinBox *m_iEdit;
};

#endif // IGRAPHBRAKE_P_H

