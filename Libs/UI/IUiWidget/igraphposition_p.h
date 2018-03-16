#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphposition.h"
#include "igraphwidget_p.h"

class AnchorItemHelper;
class WidgetItem;
class ArrowItem;
class QDoubleSpinBox;

class IUIWIDGETSHARED_EXPORT IGraphPositionPrivate:public IGraphWidgetPrivate
{
  Q_DECLARE_PUBLIC(IGraphPosition)
public:
  IGraphPositionPrivate();
  virtual ~IGraphPositionPrivate();
protected:
  AnchorItemHelper *m_anchorHelper;
  WidgetItem *m_Tstart;
  WidgetItem *m_Tend;
  WidgetItem *m_T0;
  WidgetItem *m_TM0;

  WidgetItem *m_UIF;
  WidgetItem *m_USUM0;
  WidgetItem *m_UPID;
  WidgetItem *m_USATN;
  WidgetItem *m_USUM1;
  WidgetItem *m_UVCTL;
  WidgetItem *m_USUM2;
  WidgetItem *m_UCCTL;
  WidgetItem *m_UPB;
  WidgetItem *m_UFAB;
  WidgetItem *m_UFVB;

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
  ArrowItem *m_A8;
  ArrowItem *m_A9;
  ArrowItem *m_A10;
  ArrowItem *m_A11;
  ArrowItem *m_A12;
  ArrowItem *m_A13;
  ArrowItem *m_A14;
  ArrowItem *m_A15;


  QList<ArrowItem *>m_arrowList;
  QList<WidgetItem *>m_widgetItemList;

  QDoubleSpinBox *m_pEdit;
  QDoubleSpinBox *m_accEdit;
  QDoubleSpinBox *m_velEdit;

  //饱和输出器
  WidgetItem *m_UFRAME;
  WidgetItem *m_UMAXVEL;
  WidgetItem *m_UMAXVEL_P;
  WidgetItem *m_UMAXVEL_N;

  QDoubleSpinBox *m_maxvelEdit;
  QDoubleSpinBox *m_maxvelEdit_P;
  QDoubleSpinBox *m_maxvelEdit_N;

  WidgetItem *m_T1;
  WidgetItem *m_T2;
  WidgetItem *m_T3;

  ArrowItem *m_A16;
  ArrowItem *m_A17;
  ArrowItem *m_A18;
  ArrowItem *m_A19;
  ArrowItem *m_A20;

  WidgetItem *m_TextMaxVelPositive;
  WidgetItem *m_TextMaxVelNegative;

};

#endif // IGRAPHBRAKE_P_H

