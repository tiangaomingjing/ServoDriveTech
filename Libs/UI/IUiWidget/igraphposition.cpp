#include "igraphposition.h"
#include "igraphposition_p.h"
#include "boxitemmapping.h"
#include "SDTGraphicsItems"
#include "Option"
#include "gtutils.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QDebug>
#include <QGraphicsSimpleTextItem>
#include <QTreeWidgetItem>

#define PID_POS_X -220
#define PID_POS_Y -50

IGraphPosition::~IGraphPosition()
{
  Q_D(IGraphPosition);

  foreach (WidgetItem *item, d->m_widgetItemList) {
    d->m_scene->removeItem(item);
    delete item;
    item=NULL;
  }
  d->m_widgetItemList.clear();

  foreach (ArrowItem *arrow, d->m_arrowList) {
    delete arrow;
    arrow=NULL;
  }
  d->m_arrowList.clear();
  qDebug()<<"IGraphPosition destruct-->";
}

void IGraphPosition::syncTreeDataToUiFace()
{
  Q_D(IGraphPosition);
  d->m_mapping->syncAllItem2BoxText();
}

void IGraphPosition::createItems()
{
  createInputFilterItem();
  createSumItem0();
  createPidItem();
  createSaturationItem();
  createSumItem1();
  createVelocityControllerItem();
  createSumItem2();
  createCurrentControllerItem();
  createPositionFeedbackItem();
  createFFVelocityItem();
  createFFAccelerationItem();
  createTargetItems();

  createStartEndTargetItems();
  createStartTextItem();
  createEndTextItem();

  createArrowItems();
  createAnchorItemHelper();
  createSaturationConfigItems();

  setUpItemPosAnchors();

  adjustPosition();
  setCustumBackgroundColor();
}

void IGraphPosition::setDoubleSpinBoxConnections()
{
  Q_D(IGraphPosition);
  connect(d->m_pEdit,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_accEdit,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_velEdit,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));

  connect(d->m_maxvelEdit,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_maxvelEdit_P,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_maxvelEdit_N,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
}

void IGraphPosition::installDoubleSpinBoxEventFilter()
{
  Q_D(IGraphPosition);
  d->m_pEdit->installEventFilter(this);
  d->m_accEdit->installEventFilter(this);
  d->m_velEdit->installEventFilter(this);

  d->m_maxvelEdit->installEventFilter(this);
  d->m_maxvelEdit_P->installEventFilter(this);
  d->m_maxvelEdit_N->installEventFilter(this);
}

void IGraphPosition::adjustPosition()
{
  GTUtils::delayms(10);
  Q_D(IGraphPosition);
  if(d->m_anchorHelper!=NULL)
    d->m_anchorHelper->setAnchorsActive();

  GTUtils::delayms(10);
  foreach (ArrowItem *arrow, d->m_arrowList) {
    arrow->updatePosition();
    arrow->setColor(arrowColor());
  }
}

void IGraphPosition::createInputFilterItem()
{
  Q_D(IGraphPosition);
  LabelItemWidget *label=new LabelItemWidget(tr("InputFilter"));
  label->setObjectName("label_posInputFilter");
  label->setAlignment(Qt::AlignCenter);
  d->m_UIF=new WidgetItem;
  d->m_UIF->setWidget(label,true);
  d->m_scene->addItem(d->m_UIF);

  d->m_widgetItemList.append(d->m_UIF);
}

void IGraphPosition::createSumItem0()
{
  Q_D(IGraphPosition);
  SumItemWidget *sw=new SumItemWidget;
  sw->setObjectName("sumItemWidget_posSum0");
  d->m_USUM0=new WidgetItem;
  d->m_USUM0->setWidget(sw);
  d->m_scene->addItem(d->m_USUM0);

  d->m_widgetItemList.append(d->m_USUM0);
}

void IGraphPosition::createPidItem()
{
  Q_D(IGraphPosition);

  QWidget *wpid=new QWidget;
  wpid->setObjectName("widget_posPid");
  QVBoxLayout *vlayoutTest=new QVBoxLayout(wpid);
  QLabel *title=new QLabel(tr("PID controller"),wpid);
  title->setObjectName("label_posPidTitle");
  title->setAlignment(Qt::AlignCenter);
  vlayoutTest->addWidget(title);

  QLabel *pgain=new QLabel(tr("P gain(HZ)"));
  pgain->setObjectName("label_posPgain");
  vlayoutTest->addWidget(pgain);
  QDoubleSpinBox *pedit=new QDoubleSpinBox(wpid);
  d->m_pEdit=pedit;
  pedit->setObjectName("dspinBox_posPedit");
  pedit->setMinimum(0);
  pedit->setMaximum(32767);
  pedit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  vlayoutTest->addWidget(pedit);

  wpid->setLayout(vlayoutTest);

  d->m_UPID=new WidgetItem;
  d->m_UPID->setWidget(wpid,true);
  d->m_scene->addItem(d->m_UPID);//take ownership

  d->m_widgetItemList.append(d->m_UPID);
}

void IGraphPosition::createSaturationItem()
{
  Q_D(IGraphPosition);
  QWidget *w=new QWidget;
  w->setObjectName("widget_posSaturation");
  QVBoxLayout *vlayout=new QVBoxLayout(w);
  vlayout->setMargin(2);
  SaturationItemWidget *saturation=new SaturationItemWidget(w);
  connect(saturation,SIGNAL(clicked(bool)),this,SLOT(onSaturationClicked(bool)));
  saturation->setObjectName("saturationItemWidget_posSaturation");
  vlayout->addWidget(saturation);
//  QLabel *label=new QLabel(w);
//  label->setText(tr("saturation"));
//  label->setObjectName("label_posSaturationTitle");
//  vlayout->addWidget(label);

  d->m_USATN=new WidgetItem;
  d->m_USATN->setWidget(w,true);
  d->m_scene->addItem(d->m_USATN);

  d->m_widgetItemList.append(d->m_USATN);
}

void IGraphPosition::createSumItem1()
{
  Q_D(IGraphPosition);
  SumItemWidget *sw=new SumItemWidget;
  sw->setObjectName("sumItemWidget_posSum1");
  d->m_USUM1=new WidgetItem;
  d->m_USUM1->setWidget(sw);
  d->m_scene->addItem(d->m_USUM1);

  d->m_widgetItemList.append(d->m_USUM1);
}

void IGraphPosition::createVelocityControllerItem()
{
  Q_D(IGraphPosition);
  LabelItemWidget *label=new LabelItemWidget(tr("VelCtler"));
  label->setObjectName("label_posVelCtler");
  label->setAlignment(Qt::AlignCenter);
  d->m_UVCTL=new WidgetItem;
  d->m_UVCTL->setWidget(label,true);
  d->m_scene->addItem(d->m_UVCTL);

  d->m_widgetItemList.append(d->m_UVCTL);
}

void IGraphPosition::createSumItem2()
{
  Q_D(IGraphPosition);
  SumItemWidget *sw=new SumItemWidget;
  sw->setObjectName("sumItemWidget_posSum2");
  d->m_USUM2=new WidgetItem;
  d->m_USUM2->setWidget(sw);
  d->m_scene->addItem(d->m_USUM2);

  d->m_widgetItemList.append(d->m_USUM2);
}

void IGraphPosition::createCurrentControllerItem()
{
  Q_D(IGraphPosition);
  LabelItemWidget *label=new LabelItemWidget(tr("CurCtler"));
  label->setObjectName("label_posCurCtler");
  label->setAlignment(Qt::AlignCenter);
  d->m_UCCTL=new WidgetItem;
  d->m_UCCTL->setWidget(label,true);
  d->m_scene->addItem(d->m_UCCTL);

  d->m_widgetItemList.append(d->m_UCCTL);
}

void IGraphPosition::createPositionFeedbackItem()
{
  Q_D(IGraphPosition);
  LabelItemWidget *label=new LabelItemWidget(tr("PosFeedback"));
  label->setObjectName("label_posPosFeedback");
  label->setAlignment(Qt::AlignCenter);
  d->m_UPB=new WidgetItem;
  d->m_UPB->setWidget(label,true);
  d->m_scene->addItem(d->m_UPB);

  d->m_widgetItemList.append(d->m_UPB);
}

void IGraphPosition::createFFVelocityItem()
{
  Q_D(IGraphPosition);

  QWidget *w=new QWidget;
  w->setObjectName("widget_posFFvel");
  QVBoxLayout *vlayoutTest=new QVBoxLayout(w);

  QLabel *label=new QLabel(tr("velocity feedforward (%)"));
  label->setObjectName("label_posFFvel");
  vlayoutTest->addWidget(label);
  QDoubleSpinBox *edit=new QDoubleSpinBox(w);
  edit->setMinimum(0);
  edit->setMaximum(32767);
  d->m_velEdit=edit;
  edit->setObjectName("dspinBox_posFFvel");
  edit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  vlayoutTest->addWidget(edit);

  w->setLayout(vlayoutTest);

  d->m_UFVB=new WidgetItem;
  d->m_UFVB->setWidget(w,true);
  d->m_scene->addItem(d->m_UFVB);//take ownership

  d->m_widgetItemList.append(d->m_UFVB);
}

void IGraphPosition::createFFAccelerationItem()
{
  Q_D(IGraphPosition);

  QWidget *w=new QWidget;
  w->setObjectName("widget_posFFacc");
  QVBoxLayout *vlayoutTest=new QVBoxLayout(w);

  QLabel *label=new QLabel(tr("acceleration feedforward (%)"));
  label->setObjectName("label_posFFacc");
  vlayoutTest->addWidget(label);
  QDoubleSpinBox *edit=new QDoubleSpinBox(w);
  edit->setMinimum(0);
  edit->setMaximum(32767);
  d->m_accEdit=edit;
  edit->setObjectName("dspinBox_posFFacc");
  edit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  vlayoutTest->addWidget(edit);

  w->setLayout(vlayoutTest);

  d->m_UFAB=new WidgetItem;
  d->m_UFAB->setWidget(w,true);
  d->m_scene->addItem(d->m_UFAB);//take ownership

  d->m_widgetItemList.append(d->m_UFAB);
}

void IGraphPosition::createTargetItems()
{
  Q_D(IGraphPosition);
  TargetItemWidget *t0=new TargetItemWidget;
  t0->setObjectName("targetItem_posTm0");
  d->m_TM0=new WidgetItem;
  d->m_TM0->setWidget(t0);

  t0=new TargetItemWidget;
  t0->setObjectName("targetItem_posT0");
  d->m_T0=new WidgetItem;
  d->m_T0->setWidget(t0);

  d->m_scene->addItem(d->m_TM0);
  d->m_scene->addItem(d->m_T0);

  d->m_widgetItemList.append(d->m_TM0);
  d->m_widgetItemList.append(d->m_T0);
}

void IGraphPosition::createArrowItems()
{
  Q_D(IGraphPosition);
  d->m_A0=new ArrowItem(d->m_Tstart->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UIF->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A1=new ArrowItem(d->m_UIF->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_TM0->pointF(WidgetItem::POINT_TYPE_LEFT),ArrowItem::ARROW_TYPE_STRAIGHT,"",false);
  d->m_A2=new ArrowItem(d->m_TM0->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_USUM0->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A3=new ArrowItem(d->m_USUM0->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UPID->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A4=new ArrowItem(d->m_UPID->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_USATN->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A5=new ArrowItem(d->m_USATN->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_USUM1->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A6=new ArrowItem(d->m_USUM1->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UVCTL->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A7=new ArrowItem(d->m_UVCTL->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_USUM2->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A8=new ArrowItem(d->m_USUM2->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UCCTL->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A9=new ArrowItem(d->m_UCCTL->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_Tend->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A10=new ArrowItem(d->m_TM0->pointF(WidgetItem::POINT_TYPE_TOP),d->m_UFVB->pointF(WidgetItem::POINT_TYPE_LEFT),ArrowItem::ARROW_TYPE_CORNER);
  d->m_A11=new ArrowItem(d->m_UFVB->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_USUM1->pointF(WidgetItem::POINT_TYPE_TOP),ArrowItem::ARROW_TYPE_CORNER,"+");
  d->m_A12=new ArrowItem(d->m_TM0->pointF(WidgetItem::POINT_TYPE_TOP),d->m_UFAB->pointF(WidgetItem::POINT_TYPE_LEFT),ArrowItem::ARROW_TYPE_CORNER);
  d->m_A13=new ArrowItem(d->m_UFAB->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_USUM2->pointF(WidgetItem::POINT_TYPE_TOP),ArrowItem::ARROW_TYPE_CORNER,"+");
  d->m_A14=new ArrowItem(d->m_T0->pointF(WidgetItem::POINT_TYPE_LEFT),d->m_UPB->pointF(WidgetItem::POINT_TYPE_RIGHT));
  d->m_A15=new ArrowItem(d->m_UPB->pointF(WidgetItem::POINT_TYPE_LEFT),d->m_USUM0->pointF(WidgetItem::POINT_TYPE_BOTTOM),ArrowItem::ARROW_TYPE_CORNER,"-");

  d->m_scene->addItem(d->m_A0);
  d->m_scene->addItem(d->m_A1);
  d->m_scene->addItem(d->m_A2);
  d->m_scene->addItem(d->m_A3);
  d->m_scene->addItem(d->m_A4);
  d->m_scene->addItem(d->m_A5);
  d->m_scene->addItem(d->m_A6);
  d->m_scene->addItem(d->m_A7);
  d->m_scene->addItem(d->m_A8);
  d->m_scene->addItem(d->m_A9);
  d->m_scene->addItem(d->m_A10);
  d->m_scene->addItem(d->m_A11);
  d->m_scene->addItem(d->m_A12);
  d->m_scene->addItem(d->m_A13);
  d->m_scene->addItem(d->m_A14);
  d->m_scene->addItem(d->m_A15);

  d->m_arrowList.append(d->m_A0);
  d->m_arrowList.append(d->m_A1);
  d->m_arrowList.append(d->m_A2);
  d->m_arrowList.append(d->m_A3);
  d->m_arrowList.append(d->m_A4);
  d->m_arrowList.append(d->m_A5);
  d->m_arrowList.append(d->m_A6);
  d->m_arrowList.append(d->m_A7);
  d->m_arrowList.append(d->m_A8);
  d->m_arrowList.append(d->m_A9);
  d->m_arrowList.append(d->m_A10);
  d->m_arrowList.append(d->m_A11);
  d->m_arrowList.append(d->m_A12);
  d->m_arrowList.append(d->m_A13);
  d->m_arrowList.append(d->m_A14);
  d->m_arrowList.append(d->m_A15);

}

void IGraphPosition::createSaturationConfigItems()
{
  Q_D(IGraphPosition);
  FrameItemWidget *frame=new FrameItemWidget;
  frame->setWPercent(0.1);
  frame->setMinimumSize(600,250);
  frame->setObjectName("frameItemWidget_posFrameVel");
  d->m_UFRAME=new WidgetItem;
  d->m_UFRAME->setWidget(frame);
  d->m_scene->addItem(d->m_UFRAME);
  d->m_widgetItemList.append(d->m_UFRAME);

  //max vel %
  QWidget *w=new QWidget;
  w->setObjectName("widget_posMaxVel");
  QVBoxLayout *hlayout=new QVBoxLayout(w);
  QLabel *label=new QLabel(tr("max v(%)"),w);
  label->setObjectName("label_posMaxVelPercent");
  hlayout->addWidget(label);
  QDoubleSpinBox *box=new QDoubleSpinBox(w);
  d->m_maxvelEdit=box;
  box->setMinimum(0);
  box->setMaximum(32767);
  box->setMaximumWidth(150);
  box->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(box);
  w->setLayout(hlayout);
  d->m_UMAXVEL=new WidgetItem;
  d->m_UMAXVEL->setWidget(w,true);
  d->m_scene->addItem(d->m_UMAXVEL);
  d->m_widgetItemList.append(d->m_UMAXVEL);

  //max vel_p %
  w=new QWidget;
  w->setObjectName("widget_posMaxVelPositive");
  hlayout=new QVBoxLayout(w);
  label=new QLabel(tr("positive v(%)"),w);
  label->setObjectName("label_posMaxVelPercentPositive");
  hlayout->addWidget(label);
  box=new QDoubleSpinBox(w);
  d->m_maxvelEdit_P=box;
  box->setMinimum(0);
  box->setMaximum(32767);
  box->setMaximumWidth(150);
  box->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(box);
  w->setLayout(hlayout);
  d->m_UMAXVEL_P=new WidgetItem;
  d->m_UMAXVEL_P->setWidget(w,true);
  d->m_scene->addItem(d->m_UMAXVEL_P);
  d->m_widgetItemList.append(d->m_UMAXVEL_P);

  //max vel_n %
  w=new QWidget;
  w->setObjectName("widget_posMaxVelNegative");
  hlayout=new QVBoxLayout(w);
  label=new QLabel(tr("negative v(%)"),w);
  label->setObjectName("label_posMaxVelPercentNegative");
  hlayout->addWidget(label);
  box=new QDoubleSpinBox(w);
  d->m_maxvelEdit_N=box;
  box->setMinimum(0);
  box->setMaximum(32767);
  box->setMaximumWidth(150);
  box->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(box);
  w->setLayout(hlayout);
  d->m_UMAXVEL_N=new WidgetItem;
  d->m_UMAXVEL_N->setWidget(w,true);
  d->m_scene->addItem(d->m_UMAXVEL_N);
  d->m_widgetItemList.append(d->m_UMAXVEL_N);

  TargetItemWidget *t=new TargetItemWidget;
  t->setObjectName("targetItem_posT1");
  d->m_T1=new WidgetItem;
  d->m_T1->setWidget(t);
  d->m_scene->addItem(d->m_T1);
  d->m_widgetItemList.append(d->m_T1);

  t=new TargetItemWidget;
  t->setObjectName("targetItem_posT2");
  d->m_T2=new WidgetItem;
  d->m_T2->setWidget(t);
  d->m_scene->addItem(d->m_T2);
  d->m_widgetItemList.append(d->m_T2);

  t=new TargetItemWidget;
  t->setObjectName("targetItem_posT3");
  d->m_T3=new WidgetItem;
  d->m_T3->setWidget(t);
  d->m_scene->addItem(d->m_T3);
  d->m_widgetItemList.append(d->m_T3);

  //arrows
  d->m_A16=new ArrowItem(d->m_UMAXVEL->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_T1->pointF(WidgetItem::POINT_TYPE_LEFT),ArrowItem::ARROW_TYPE_STRAIGHT,"",false);
  d->m_A17=new ArrowItem(d->m_T1->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UMAXVEL_P->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A18=new ArrowItem(d->m_T1->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UMAXVEL_N->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A19=new ArrowItem(d->m_UMAXVEL_P->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_T2->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A20=new ArrowItem(d->m_UMAXVEL_N->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_T3->pointF(WidgetItem::POINT_TYPE_LEFT));

  d->m_scene->addItem(d->m_A16);
  d->m_scene->addItem(d->m_A17);
  d->m_scene->addItem(d->m_A18);
  d->m_scene->addItem(d->m_A19);
  d->m_scene->addItem(d->m_A20);

  d->m_arrowList.append(d->m_A16);
  d->m_arrowList.append(d->m_A17);
  d->m_arrowList.append(d->m_A18);
  d->m_arrowList.append(d->m_A19);
  d->m_arrowList.append(d->m_A20);

  //text
  label=new QLabel(tr("positive MaxV"));
  label->setObjectName("label_posTextPositiveMaxV");
  d->m_TextMaxVelPositive=new WidgetItem;
  d->m_TextMaxVelPositive->setWidget(label);
  d->m_scene->addItem(d->m_TextMaxVelPositive);
  d->m_widgetItemList.append(d->m_TextMaxVelPositive);

  label=new QLabel(tr("negative MaxV"));
  label->setObjectName("label_posTextNegativeMaxV");
  d->m_TextMaxVelNegative=new WidgetItem;
  d->m_TextMaxVelNegative->setWidget(label);
  d->m_scene->addItem(d->m_TextMaxVelNegative);
  d->m_widgetItemList.append(d->m_TextMaxVelNegative);

  setSaturationConfigVisible(false);
}

void IGraphPosition::createStartEndTargetItems()
{
  Q_D(IGraphPosition);
  TargetItemWidget *t0=new TargetItemWidget;
  t0->setObjectName("targetItem_posTstart");
  d->m_Tstart=new WidgetItem;
  d->m_Tstart->setWidget(t0);

  t0=new TargetItemWidget;
  t0->setObjectName("targetItem_posTend");
  d->m_Tend=new WidgetItem;
  d->m_Tend->setWidget(t0);

  d->m_scene->addItem(d->m_Tstart);
  d->m_scene->addItem(d->m_Tend);

  d->m_widgetItemList.append(d->m_Tstart);
  d->m_widgetItemList.append(d->m_Tend);
}

void IGraphPosition::createStartTextItem()
{
  Q_D(IGraphPosition);

  LabelItemWidget *label=new LabelItemWidget(tr("pos cmd"));
  label->setObjectName("label_posStartText");
  d->m_TextStart=new WidgetItem;
  d->m_TextStart->setWidget(label);
  d->m_scene->addItem(d->m_TextStart);
  d->m_widgetItemList.append(d->m_TextStart);
}

void IGraphPosition::createEndTextItem()
{
  Q_D(IGraphPosition);

  LabelItemWidget *label=new LabelItemWidget(tr("cur/torque output"));
  label->setObjectName("label_posEndText");
  label->setAlignment(Qt::AlignRight);
  d->m_TextEnd=new WidgetItem;
  d->m_TextEnd->setWidget(label);
  d->m_scene->addItem(d->m_TextEnd);

  d->m_widgetItemList.append(d->m_TextEnd);
}

void IGraphPosition::createAnchorItemHelper()
{
  Q_D(IGraphPosition);
  d->m_anchorHelper=new AnchorItemHelper(this);
}

void IGraphPosition::setUpItemPosAnchors()
{
  Q_D(IGraphPosition);
  d->m_UPID->setPos(PID_POS_X,PID_POS_Y);
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_USUM0,AnchorItemHelper::AnchorLeft,-1.5*d->m_USUM0->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_USUM0,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_USUM0,d->m_TM0,AnchorItemHelper::AnchorLeft,-1*d->m_USUM0->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_USUM0,d->m_TM0,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_TM0,d->m_UIF,AnchorItemHelper::AnchorLeft,-1.2*d->m_UIF->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_TM0,d->m_UIF,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UIF,d->m_Tstart,AnchorItemHelper::AnchorLeft,-0.7*d->m_UIF->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UIF,d->m_Tstart,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_USATN,AnchorItemHelper::AnchorRight,1.5*d->m_USATN->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_USATN,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_USATN,d->m_USUM1,AnchorItemHelper::AnchorRight,1.5*d->m_USUM1->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_USATN,d->m_USUM1,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_USUM1,d->m_UVCTL,AnchorItemHelper::AnchorRight,1.4*d->m_UVCTL->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_USUM1,d->m_UVCTL,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UVCTL,d->m_USUM2,AnchorItemHelper::AnchorRight,1.6*d->m_USUM2->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UVCTL,d->m_USUM2,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_USUM2,d->m_UCCTL,AnchorItemHelper::AnchorRight,d->m_UCCTL->boundingRect().width()+d->m_USUM2->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_USUM2,d->m_UCCTL,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UCCTL,d->m_Tend,AnchorItemHelper::AnchorRight,d->m_UCCTL->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UCCTL,d->m_Tend,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_UFVB,AnchorItemHelper::AnchorHorizontalCenter);
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_UFVB,AnchorItemHelper::AnchorTop,-1.5*d->m_UFVB->boundingRect().height());

  d->m_anchorHelper->addAnchor(d->m_UFVB,d->m_UFAB,AnchorItemHelper::AnchorHorizontalCenter);
  d->m_anchorHelper->addAnchor(d->m_UFVB,d->m_UFAB,AnchorItemHelper::AnchorTop,-1.5*d->m_UFAB->boundingRect().height());

  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_UPB,AnchorItemHelper::AnchorHorizontalCenter);
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_UPB,AnchorItemHelper::AnchorBottom,2*d->m_UPB->boundingRect().height());

  d->m_anchorHelper->addAnchor(d->m_UPB,d->m_T0,AnchorItemHelper::AnchorRight,2*d->m_UPB->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UPB,d->m_T0,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_Tstart,d->m_TextStart,AnchorItemHelper::AnchorLeft,1.2*d->m_Tstart->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_Tstart,d->m_TextStart,AnchorItemHelper::AnchorBottom,-15);

  d->m_anchorHelper->addAnchor(d->m_Tend,d->m_TextEnd,AnchorItemHelper::AnchorRight,-1.2*d->m_Tend->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_Tend,d->m_TextEnd,AnchorItemHelper::AnchorBottom,-15);


  //saturation config widget
  double hp=dynamic_cast<FrameItemWidget*>(d->m_UFRAME->widget())->getHPercent();
  double oft=((1-hp)/2-hp)*d->m_UFRAME->boundingRect().height();
  d->m_anchorHelper->addAnchor(d->m_USATN,d->m_UFRAME,AnchorItemHelper::AnchorHorizontalCenter);
  d->m_anchorHelper->addAnchor(d->m_USATN,d->m_UFRAME,AnchorItemHelper::AnchorBottom,d->m_UFRAME->boundingRect().height());

  d->m_anchorHelper->addAnchor(d->m_UFRAME,d->m_UMAXVEL,AnchorItemHelper::AnchorLeft,20);
  d->m_anchorHelper->addAnchor(d->m_UFRAME,d->m_UMAXVEL,AnchorItemHelper::AnchorVerticalCenter,oft);

  d->m_anchorHelper->addAnchor(d->m_UMAXVEL,d->m_T1,AnchorItemHelper::AnchorRight,30);
  d->m_anchorHelper->addAnchor(d->m_UMAXVEL,d->m_T1,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_T1,d->m_UMAXVEL_P,AnchorItemHelper::AnchorRight,d->m_UMAXVEL_P->boundingRect().width()+30);
  d->m_anchorHelper->addAnchor(d->m_T1,d->m_UMAXVEL_P,AnchorItemHelper::AnchorVerticalCenter,-1*d->m_UMAXVEL->boundingRect().height()/2-10);

  d->m_anchorHelper->addAnchor(d->m_T1,d->m_UMAXVEL_N,AnchorItemHelper::AnchorRight,d->m_UMAXVEL_N->boundingRect().width()+30);
  d->m_anchorHelper->addAnchor(d->m_T1,d->m_UMAXVEL_N,AnchorItemHelper::AnchorVerticalCenter,1*d->m_UMAXVEL->boundingRect().height()/2+10);

  d->m_anchorHelper->addAnchor(d->m_UMAXVEL_P,d->m_T2,AnchorItemHelper::AnchorRight,30);
  d->m_anchorHelper->addAnchor(d->m_UMAXVEL_P,d->m_T2,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UMAXVEL_N,d->m_T3,AnchorItemHelper::AnchorRight,30);
  d->m_anchorHelper->addAnchor(d->m_UMAXVEL_N,d->m_T3,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_T2,d->m_TextMaxVelPositive,AnchorItemHelper::AnchorRight,d->m_TextMaxVelPositive->boundingRect().width()+5);
  d->m_anchorHelper->addAnchor(d->m_T2,d->m_TextMaxVelPositive,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_T3,d->m_TextMaxVelNegative,AnchorItemHelper::AnchorRight,d->m_TextMaxVelNegative->boundingRect().width()+5);
  d->m_anchorHelper->addAnchor(d->m_T3,d->m_TextMaxVelNegative,AnchorItemHelper::AnchorVerticalCenter);
}

bool IGraphPosition::eventFilter(QObject *obj, QEvent *event)
{

  if (event->type()==QEvent::KeyPress)
  {
    qDebug()<<"IGraphPosition::eventFilter";
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
    {
      Q_D(IGraphPosition);
      qDebug()<<"enter clicked"<<"object name"<<obj->objectName();
      QDoubleSpinBox* box=dynamic_cast<QDoubleSpinBox*>(obj);
      d->m_mapping->syncBoxText2Item(box);
//      d->m_mapping->syncBoxText2MultiItem(box);
      setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_READY);
      return true;
    }
  }
  return InteractiveView::eventFilter(obj,event);
}

void IGraphPosition::onSaturationClicked(bool checked)
{
  setSaturationConfigVisible(checked);
}

void IGraphPosition::setSaturationConfigVisible(bool enable)
{
  Q_D(IGraphPosition);
  d->m_UFRAME->setVisible(enable);

  d->m_UMAXVEL->setVisible(enable);
  d->m_UMAXVEL_P->setVisible(enable);
  d->m_UMAXVEL_N->setVisible(enable);


  d->m_T1->setVisible(enable);
  d->m_T2->setVisible(enable);
  d->m_T3->setVisible(enable);

  d->m_A16->setVisible(enable);
  d->m_A17->setVisible(enable);
  d->m_A18->setVisible(enable);
  d->m_A19->setVisible(enable);
  d->m_A20->setVisible(enable);

  d->m_TextMaxVelPositive->setVisible(enable);
  d->m_TextMaxVelNegative->setVisible(enable);
}


IGraphPosition::IGraphPosition(IGraphPositionPrivate &dd, QWidget *parent):IGraphWidget(dd,parent)
{

}
