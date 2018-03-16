#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphvelocity.h"
#include "igraphwidget_p.h"

class AnchorItemHelper;
class WidgetItem;
class ArrowItem;
class QDoubleSpinBox;

class IUIWIDGETSHARED_EXPORT IGraphVelocityPrivate:public IGraphWidgetPrivate
{
  Q_DECLARE_PUBLIC(IGraphVelocity)
public:
  IGraphVelocityPrivate();
  virtual ~IGraphVelocityPrivate();
protected:
  AnchorItemHelper *m_anchorHelper;
  WidgetItem *m_Tstart;
  WidgetItem *m_Tend;
  WidgetItem *m_T0;

  WidgetItem *m_UIF;
  WidgetItem *m_USUM;
  WidgetItem *m_UPID;
  WidgetItem *m_USATN;
  WidgetItem *m_UOF;
  WidgetItem *m_UVB;

  WidgetItem *m_TextStart;
  WidgetItem *m_TextEnd;

  ArrowItem *m_A0;
  ArrowItem *m_A1;
  ArrowItem *m_A2;
  ArrowItem *m_A3;
  ArrowItem *m_A4;
  ArrowItem *m_A5;
  ArrowItem *m_A6;
  ArrowItem *m_A7;

  QList<ArrowItem *>m_arrowList;
  QList<WidgetItem *>m_widgetItemList;

  QDoubleSpinBox *m_pEdit;
  QDoubleSpinBox *m_iEdit;

  //饱和输出器
  WidgetItem *m_UFRAME;
  WidgetItem *m_UMAXTQ;
  WidgetItem *m_UMAXTQ_P;
  WidgetItem *m_UMAXTQ_N;

  QDoubleSpinBox *m_maxTqEdit;
  QDoubleSpinBox *m_maxTqEdit_P;
  QDoubleSpinBox *m_maxTqEdit_N;

  WidgetItem *m_T1;
  WidgetItem *m_T2;
  WidgetItem *m_T3;

  ArrowItem *m_A8;
  ArrowItem *m_A9;
  ArrowItem *m_A10;
  ArrowItem *m_A11;
  ArrowItem *m_A12;

  WidgetItem *m_TextMaxTqPositive;
  WidgetItem *m_TextMaxTqNegative;
};

#endif // IGRAPHBRAKE_P_H

