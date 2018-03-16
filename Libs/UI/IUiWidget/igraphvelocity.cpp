#include "igraphvelocity.h"
#include "igraphvelocity_p.h"
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

#define PID_POS_X -60
#define PID_POS_Y -85

IGraphVelocityPrivate::IGraphVelocityPrivate()
{

}

IGraphVelocityPrivate::~IGraphVelocityPrivate()
{

}

IGraphVelocity::~IGraphVelocity()
{
  Q_D(IGraphVelocity);

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
  qDebug()<<"IGraphVelocity destruct-->";
}

void IGraphVelocity::syncTreeDataToUiFace()
{
  Q_D(IGraphVelocity);
  d->m_mapping->syncAllItem2BoxText();
}

void IGraphVelocity::createItems()
{
  createInputFilterItem();
  createSumItem();
  createPidItem();
  createSaturationItem();
  createOutputFilterItem();
  createVelocityFeedbackItem();

  createTargetItems();

  createStartEndTargetItems();
  createStartTextItem();
  createEndTextItem();

  createArrowItems();
  createSaturationConfigItems();
  createAnchorItemHelper();
  setUpItemPosAnchors();

  adjustPosition();
  setCustumBackgroundColor();
}

void IGraphVelocity::setDoubleSpinBoxConnections()
{
  Q_D(IGraphVelocity);
  connect(d->m_pEdit,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_iEdit,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_maxTqEdit,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));

  connect(d->m_maxTqEdit_P,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_maxTqEdit_N,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));

}

void IGraphVelocity::installDoubleSpinBoxEventFilter()
{
  Q_D(IGraphVelocity);
  d->m_pEdit->installEventFilter(this);
  d->m_iEdit->installEventFilter(this);
  d->m_maxTqEdit->installEventFilter(this);

  d->m_maxTqEdit_P->installEventFilter(this);
  d->m_maxTqEdit_N->installEventFilter(this);
}

void IGraphVelocity::adjustPosition()
{
  GTUtils::delayms(10);
  Q_D(IGraphVelocity);
  if(d->m_anchorHelper!=NULL)
    d->m_anchorHelper->setAnchorsActive();

  GTUtils::delayms(10);
  foreach (ArrowItem *arrow, d->m_arrowList) {
    arrow->updatePosition();
    arrow->setColor(arrowColor());
  }
}

void IGraphVelocity::createInputFilterItem()
{
  Q_D(IGraphVelocity);
  LabelItemWidget *label=new LabelItemWidget(tr("InputFilter"));
  label->setObjectName("label_velInputFilter");
  label->setAlignment(Qt::AlignCenter);
  d->m_UIF=new WidgetItem;
  d->m_UIF->setWidget(label,true);
  d->m_scene->addItem(d->m_UIF);

  d->m_widgetItemList.append(d->m_UIF);
}

void IGraphVelocity::createSumItem()
{
  Q_D(IGraphVelocity);
  SumItemWidget *sw=new SumItemWidget;
  sw->setObjectName("sumItemWidget_velSum");
  d->m_USUM=new WidgetItem;
  d->m_USUM->setWidget(sw);
  d->m_scene->addItem(d->m_USUM);

  d->m_widgetItemList.append(d->m_USUM);
}

void IGraphVelocity::createPidItem()
{
  Q_D(IGraphVelocity);

  QWidget *wpid=new QWidget;
  wpid->setObjectName("widget_velPid");
  QVBoxLayout *vlayoutTest=new QVBoxLayout(wpid);
  QLabel *title=new QLabel(tr("PID controller"),wpid);
  title->setObjectName("label_velPidTitle");
  title->setAlignment(Qt::AlignCenter);
  vlayoutTest->addWidget(title);

  QLabel *pgain=new QLabel(tr("P gain(HZ)"));
  pgain->setObjectName("label_velPgain");
  vlayoutTest->addWidget(pgain);
  QDoubleSpinBox *pedit=new QDoubleSpinBox(wpid);
  d->m_pEdit=pedit;
  pedit->setObjectName("dspinBox_velPedit");
  pedit->setMinimum(-32768);
  pedit->setMaximum(32767);
  pedit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  vlayoutTest->addWidget(pedit);

  QLabel *igain=new QLabel(tr("I gain(ms)"),wpid);
  igain->setObjectName("label_velIgain");
  vlayoutTest->addWidget(igain);
  QDoubleSpinBox *iedit=new QDoubleSpinBox(wpid);
  d->m_iEdit=iedit;
  iedit->setObjectName("dspinBox_velIedit");
  iedit->setMinimum(0);
  iedit->setMaximum(65535);
  iedit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  vlayoutTest->addWidget(iedit);

  wpid->setLayout(vlayoutTest);

  d->m_UPID=new WidgetItem;
  d->m_UPID->setWidget(wpid,true);
  d->m_UPID->setObjectName("pid");
  d->m_scene->addItem(d->m_UPID);//take ownership

  d->m_widgetItemList.append(d->m_UPID);
}

void IGraphVelocity::createSaturationItem()
{
  Q_D(IGraphVelocity);
  QWidget *w=new QWidget;
  w->setObjectName("widget_velSaturation");
  QVBoxLayout *vlayout=new QVBoxLayout(w);
  vlayout->setMargin(2);
  SaturationItemWidget *saturation=new SaturationItemWidget(w);
  connect(saturation,SIGNAL(clicked(bool)),this,SLOT(onSaturationClicked(bool)));
  saturation->setObjectName("saturationItemWidget_velSaturation");
  vlayout->addWidget(saturation);

  d->m_USATN=new WidgetItem;
  d->m_USATN->setWidget(w,true);
  d->m_scene->addItem(d->m_USATN);

  d->m_widgetItemList.append(d->m_USATN);
}

void IGraphVelocity::createOutputFilterItem()
{
  Q_D(IGraphVelocity);
  LabelItemWidget *label=new LabelItemWidget(tr("OutputFilter"));
  label->setObjectName("label_velOutputFilter");
  label->setAlignment(Qt::AlignCenter);
  d->m_UOF=new WidgetItem;
  d->m_UOF->setWidget(label,true);
  d->m_scene->addItem(d->m_UOF);

  d->m_widgetItemList.append(d->m_UOF);
}

void IGraphVelocity::createVelocityFeedbackItem()
{
  Q_D(IGraphVelocity);
  LabelItemWidget *label=new LabelItemWidget(tr("VelFeedback"));
  label->setObjectName("label_velVelocityFeedback");
  label->setAlignment(Qt::AlignCenter);
  d->m_UVB=new WidgetItem;
  d->m_UVB->setWidget(label,true);
  d->m_scene->addItem(d->m_UVB);

  d->m_widgetItemList.append(d->m_UVB);
}

void IGraphVelocity::createTargetItems()
{
  Q_D(IGraphVelocity);
  TargetItemWidget *t0=new TargetItemWidget;
  t0->setObjectName("targetItem_velT0");
  d->m_T0=new WidgetItem;
  d->m_T0->setWidget(t0);

  d->m_scene->addItem(d->m_T0);

  d->m_widgetItemList.append(d->m_T0);
}

void IGraphVelocity::createStartEndTargetItems()
{
  Q_D(IGraphVelocity);
  TargetItemWidget *t0=new TargetItemWidget;
  t0->setObjectName("targetItem_velTstart");
  d->m_Tstart=new WidgetItem;
  d->m_Tstart->setWidget(t0);

  t0=new TargetItemWidget;
  t0->setObjectName("targetItem_velTend");
  d->m_Tend=new WidgetItem;
  d->m_Tend->setWidget(t0);

  d->m_scene->addItem(d->m_Tstart);
  d->m_scene->addItem(d->m_Tend);

  d->m_widgetItemList.append(d->m_Tstart);
  d->m_widgetItemList.append(d->m_Tend);
}

void IGraphVelocity::createStartTextItem()
{
  Q_D(IGraphVelocity);

  LabelItemWidget *label=new LabelItemWidget(tr("velcmd"));
  label->setObjectName("label_velStartText");
  d->m_TextStart=new WidgetItem;
  d->m_TextStart->setWidget(label);
  d->m_scene->addItem(d->m_TextStart);
  d->m_widgetItemList.append(d->m_TextStart);
}

void IGraphVelocity::createEndTextItem()
{
  Q_D(IGraphVelocity);

  LabelItemWidget *label=new LabelItemWidget(tr("velctler out"));
  label->setObjectName("label_velEndText");
  d->m_TextEnd=new WidgetItem;
  d->m_TextEnd->setWidget(label);
  d->m_scene->addItem(d->m_TextEnd);
  d->m_widgetItemList.append(d->m_TextEnd);
}

void IGraphVelocity::createArrowItems()
{
  Q_D(IGraphVelocity);
  d->m_A0=new ArrowItem(d->m_Tstart->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UIF->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A1=new ArrowItem(d->m_UIF->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_USUM->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A2=new ArrowItem(d->m_USUM->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UPID->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A3=new ArrowItem(d->m_UPID->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_USATN->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A4=new ArrowItem(d->m_USATN->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UOF->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A5=new ArrowItem(d->m_UOF->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_Tend->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A6=new ArrowItem(d->m_T0->pointF(WidgetItem::POINT_TYPE_LEFT),d->m_UVB->pointF(WidgetItem::POINT_TYPE_RIGHT));
  d->m_A7=new ArrowItem(d->m_UVB->pointF(WidgetItem::POINT_TYPE_LEFT),d->m_USUM->pointF(WidgetItem::POINT_TYPE_BOTTOM),ArrowItem::ARROW_TYPE_CORNER,"-");

  d->m_scene->addItem(d->m_A0);
  d->m_scene->addItem(d->m_A1);
  d->m_scene->addItem(d->m_A2);
  d->m_scene->addItem(d->m_A3);
  d->m_scene->addItem(d->m_A4);
  d->m_scene->addItem(d->m_A5);
  d->m_scene->addItem(d->m_A6);
  d->m_scene->addItem(d->m_A7);

  d->m_arrowList.append(d->m_A0);
  d->m_arrowList.append(d->m_A1);
  d->m_arrowList.append(d->m_A2);
  d->m_arrowList.append(d->m_A3);
  d->m_arrowList.append(d->m_A4);
  d->m_arrowList.append(d->m_A5);
  d->m_arrowList.append(d->m_A6);
  d->m_arrowList.append(d->m_A7);
}

void IGraphVelocity::createSaturationConfigItems()
{
  Q_D(IGraphVelocity);
  FrameItemWidget *frame=new FrameItemWidget;
  frame->setWPercent(0.1);
  frame->setPosPercent(0.65);
  frame->setVertexPercent(0.65);
  frame->setMode(1);
  frame->setMinimumSize(600,250);
  frame->setObjectName("frameItemWidget_velFrameVel");
  d->m_UFRAME=new WidgetItem;
  d->m_UFRAME->setWidget(frame);
  d->m_scene->addItem(d->m_UFRAME);
  d->m_widgetItemList.append(d->m_UFRAME);

  //max torque %
  QWidget *w=new QWidget;
  w->setObjectName("widget_velMaxTq");
  QVBoxLayout *hlayout=new QVBoxLayout(w);
  QLabel *label=new QLabel(tr("max Tq(%)"),w);
  label->setObjectName("label_velMaxTqPercent");
  hlayout->addWidget(label);
  QDoubleSpinBox *box=new QDoubleSpinBox(w);
  d->m_maxTqEdit=box;
  box->setMinimum(0);
  box->setMaximum(32767);
  box->setMaximumWidth(150);
  box->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(box);
  w->setLayout(hlayout);
  d->m_UMAXTQ=new WidgetItem;
  d->m_UMAXTQ->setWidget(w,true);
  d->m_scene->addItem(d->m_UMAXTQ);
  d->m_widgetItemList.append(d->m_UMAXTQ);

  //max tq_p %
  w=new QWidget;
  w->setObjectName("widget_velMaxTqPositive");
  hlayout=new QVBoxLayout(w);
  label=new QLabel(tr("positive Tq(%)"),w);
  label->setObjectName("label_velMaxTqPercentPositive");
  hlayout->addWidget(label);
  box=new QDoubleSpinBox(w);
  d->m_maxTqEdit_P=box;
  box->setMinimum(0);
  box->setMaximum(32767);
  box->setMaximumWidth(150);
  box->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(box);
  w->setLayout(hlayout);
  d->m_UMAXTQ_P=new WidgetItem;
  d->m_UMAXTQ_P->setWidget(w,true);
  d->m_scene->addItem(d->m_UMAXTQ_P);
  d->m_widgetItemList.append(d->m_UMAXTQ_P);

  //max tq_n %
  w=new QWidget;
  w->setObjectName("widget_velMaxTqNegative");
  hlayout=new QVBoxLayout(w);
  label=new QLabel(tr("negative Tq(%)"),w);
  label->setObjectName("label_velMaxTqPercentNegative");
  hlayout->addWidget(label);
  box=new QDoubleSpinBox(w);
  d->m_maxTqEdit_N=box;
  box->setMinimum(0);
  box->setMaximum(32767);
  box->setMaximumWidth(150);
  box->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(box);
  w->setLayout(hlayout);
  d->m_UMAXTQ_N=new WidgetItem;
  d->m_UMAXTQ_N->setWidget(w,true);
  d->m_scene->addItem(d->m_UMAXTQ_N);
  d->m_widgetItemList.append(d->m_UMAXTQ_N);

  TargetItemWidget *t=new TargetItemWidget;
  t->setObjectName("targetItem_velT1");
  d->m_T1=new WidgetItem;
  d->m_T1->setWidget(t);
  d->m_scene->addItem(d->m_T1);
  d->m_widgetItemList.append(d->m_T1);

  t=new TargetItemWidget;
  t->setObjectName("targetItem_velT2");
  d->m_T2=new WidgetItem;
  d->m_T2->setWidget(t);
  d->m_scene->addItem(d->m_T2);
  d->m_widgetItemList.append(d->m_T2);

  t=new TargetItemWidget;
  t->setObjectName("targetItem_velT3");
  d->m_T3=new WidgetItem;
  d->m_T3->setWidget(t);
  d->m_scene->addItem(d->m_T3);
  d->m_widgetItemList.append(d->m_T3);

  //arrows
  d->m_A8=new ArrowItem(d->m_UMAXTQ->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_T1->pointF(WidgetItem::POINT_TYPE_LEFT),ArrowItem::ARROW_TYPE_STRAIGHT,"",false);
  d->m_A9=new ArrowItem(d->m_T1->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UMAXTQ_P->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A10=new ArrowItem(d->m_T1->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UMAXTQ_N->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A11=new ArrowItem(d->m_UMAXTQ_P->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_T2->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A12=new ArrowItem(d->m_UMAXTQ_N->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_T3->pointF(WidgetItem::POINT_TYPE_LEFT));

  d->m_scene->addItem(d->m_A8);
  d->m_scene->addItem(d->m_A9);
  d->m_scene->addItem(d->m_A10);
  d->m_scene->addItem(d->m_A11);
  d->m_scene->addItem(d->m_A12);

  d->m_arrowList.append(d->m_A8);
  d->m_arrowList.append(d->m_A9);
  d->m_arrowList.append(d->m_A10);
  d->m_arrowList.append(d->m_A11);
  d->m_arrowList.append(d->m_A12);

  //text
  label=new QLabel(tr("positive MaxTq"));
  label->setObjectName("label_velTextPositiveMaxTq");
  d->m_TextMaxTqPositive=new WidgetItem;
  d->m_TextMaxTqPositive->setWidget(label);
  d->m_scene->addItem(d->m_TextMaxTqPositive);
  d->m_widgetItemList.append(d->m_TextMaxTqPositive);

  label=new QLabel(tr("negative MaxTq"));
  label->setObjectName("label_velTextNegativeMaxTq");
  d->m_TextMaxTqNegative=new WidgetItem;
  d->m_TextMaxTqNegative->setWidget(label);
  d->m_scene->addItem(d->m_TextMaxTqNegative);
  d->m_widgetItemList.append(d->m_TextMaxTqNegative);

  setSaturationConfigVisible(false);
}

void IGraphVelocity::createAnchorItemHelper()
{
  Q_D(IGraphVelocity);
  d->m_anchorHelper=new AnchorItemHelper(this);
}

void IGraphVelocity::setUpItemPosAnchors()
{
  Q_D(IGraphVelocity);
  d->m_UPID->setPos(PID_POS_X,PID_POS_Y);
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_USATN,AnchorItemHelper::AnchorRight,1.5*d->m_USATN->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_USATN,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_USATN,d->m_UOF,AnchorItemHelper::AnchorRight,1.5*d->m_UOF->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_USATN,d->m_UOF,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UOF,d->m_Tend,AnchorItemHelper::AnchorRight,100);
  d->m_anchorHelper->addAnchor(d->m_UOF,d->m_Tend,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_USUM,AnchorItemHelper::AnchorLeft,-2*d->m_USUM->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_USUM,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_USUM,d->m_UIF,AnchorItemHelper::AnchorLeft,-1*d->m_UIF->boundingRect().width()-d->m_USUM->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_USUM,d->m_UIF,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UIF,d->m_Tstart,AnchorItemHelper::AnchorLeft,-100);
  d->m_anchorHelper->addAnchor(d->m_UIF,d->m_Tstart,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_UVB,AnchorItemHelper::AnchorHorizontalCenter,50);
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_UVB,AnchorItemHelper::AnchorBottom,2*d->m_UVB->boundingRect().height());

  d->m_anchorHelper->addAnchor(d->m_UVB,d->m_T0,AnchorItemHelper::AnchorRight,50);
  d->m_anchorHelper->addAnchor(d->m_UVB,d->m_T0,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_Tstart,d->m_TextStart,AnchorItemHelper::AnchorLeft,1.2*d->m_Tstart->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_Tstart,d->m_TextStart,AnchorItemHelper::AnchorBottom,-15);

  d->m_anchorHelper->addAnchor(d->m_Tend,d->m_TextEnd,AnchorItemHelper::AnchorRight,-1.2*d->m_Tend->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_Tend,d->m_TextEnd,AnchorItemHelper::AnchorBottom,-15);


  //saturation config widget
  double wp=dynamic_cast<FrameItemWidget*>(d->m_UFRAME->widget())->getPosPercent();
  double hp=dynamic_cast<FrameItemWidget*>(d->m_UFRAME->widget())->getHPercent();
  double oft=-1*(wp-0.5)*d->m_UFRAME->boundingRect().width();
  d->m_anchorHelper->addAnchor(d->m_USATN,d->m_UFRAME,AnchorItemHelper::AnchorHorizontalCenter,oft);
  d->m_anchorHelper->addAnchor(d->m_USATN,d->m_UFRAME,AnchorItemHelper::AnchorBottom,-1*d->m_USATN->boundingRect().height()-10);

  oft=-1*((1-hp)/2-hp)*d->m_UFRAME->boundingRect().height();
  d->m_anchorHelper->addAnchor(d->m_UFRAME,d->m_UMAXTQ,AnchorItemHelper::AnchorLeft,20);
  d->m_anchorHelper->addAnchor(d->m_UFRAME,d->m_UMAXTQ,AnchorItemHelper::AnchorVerticalCenter,oft);

  d->m_anchorHelper->addAnchor(d->m_UMAXTQ,d->m_T1,AnchorItemHelper::AnchorRight,30);
  d->m_anchorHelper->addAnchor(d->m_UMAXTQ,d->m_T1,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_T1,d->m_UMAXTQ_P,AnchorItemHelper::AnchorRight,d->m_UMAXTQ_P->boundingRect().width()+30);
  d->m_anchorHelper->addAnchor(d->m_T1,d->m_UMAXTQ_P,AnchorItemHelper::AnchorVerticalCenter,-1*d->m_UMAXTQ->boundingRect().height()/2-10);

  d->m_anchorHelper->addAnchor(d->m_T1,d->m_UMAXTQ_N,AnchorItemHelper::AnchorRight,d->m_UMAXTQ_N->boundingRect().width()+30);
  d->m_anchorHelper->addAnchor(d->m_T1,d->m_UMAXTQ_N,AnchorItemHelper::AnchorVerticalCenter,1*d->m_UMAXTQ->boundingRect().height()/2+10);

  d->m_anchorHelper->addAnchor(d->m_UMAXTQ_P,d->m_T2,AnchorItemHelper::AnchorRight,30);
  d->m_anchorHelper->addAnchor(d->m_UMAXTQ_P,d->m_T2,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UMAXTQ_N,d->m_T3,AnchorItemHelper::AnchorRight,30);
  d->m_anchorHelper->addAnchor(d->m_UMAXTQ_N,d->m_T3,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_T2,d->m_TextMaxTqPositive,AnchorItemHelper::AnchorRight,d->m_TextMaxTqPositive->boundingRect().width()+5);
  d->m_anchorHelper->addAnchor(d->m_T2,d->m_TextMaxTqPositive,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_T3,d->m_TextMaxTqNegative,AnchorItemHelper::AnchorRight,d->m_TextMaxTqNegative->boundingRect().width()+5);
  d->m_anchorHelper->addAnchor(d->m_T3,d->m_TextMaxTqNegative,AnchorItemHelper::AnchorVerticalCenter);
}

void IGraphVelocity::onSaturationClicked(bool checked)
{
  setSaturationConfigVisible(checked);
}

void IGraphVelocity::setSaturationConfigVisible(bool enable)
{
  Q_D(IGraphVelocity);
  d->m_UFRAME->setVisible(enable);

  d->m_UMAXTQ->setVisible(enable);
  d->m_UMAXTQ_P->setVisible(enable);
  d->m_UMAXTQ_N->setVisible(enable);


  d->m_T1->setVisible(enable);
  d->m_T2->setVisible(enable);
  d->m_T3->setVisible(enable);

  d->m_A8->setVisible(enable);
  d->m_A9->setVisible(enable);
  d->m_A10->setVisible(enable);
  d->m_A11->setVisible(enable);
  d->m_A12->setVisible(enable);

  d->m_TextMaxTqPositive->setVisible(enable);
  d->m_TextMaxTqNegative->setVisible(enable);
}


IGraphVelocity::IGraphVelocity(IGraphVelocityPrivate &dd, QWidget *parent):IGraphWidget(dd,parent)
{

}
