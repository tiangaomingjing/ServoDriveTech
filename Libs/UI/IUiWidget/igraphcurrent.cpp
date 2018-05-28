#include "igraphcurrent.h"
#include "igraphcurrent_p.h"
#include "SDTGraphicsItems"
#include "Option"
#include "boxitemmapping.h"

#include "gtutils.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QDebug>
#include <QGraphicsSimpleTextItem>
#include <QTreeWidgetItem>
#include <QDebug>

#define PID_POS_X -50
#define PID_POS_Y -100

IGraphCurrent::~IGraphCurrent()
{

  Q_D(IGraphCurrent);

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


  qDebug()<<"IGraphCurrent destruct-->";
}

void IGraphCurrent::syncTreeDataToUiFace()
{
  Q_D(IGraphCurrent);
  d->m_mapping->syncAllItem2BoxText();
}

bool IGraphCurrent::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type()==QEvent::KeyPress)
  {
    qDebug()<<"IGraphCurrent::eventFilter";
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
    {
      Q_D(IGraphCurrent);
      qDebug()<<"enter clicked"<<"object name"<<obj->objectName()<<"syncBoxText2MultiItem";
      QDoubleSpinBox* box=dynamic_cast<QDoubleSpinBox*>(obj);
      d->m_mapping->syncBoxText2MultiItem(box);
      setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_READY);
      return true;
    }
  }
  return InteractiveView::eventFilter(obj,event);
}

void IGraphCurrent::createPidControllerItem()
{
  Q_D(IGraphCurrent);

  QWidget *wpid=new QWidget;
  wpid->setObjectName("widget_currentPid");
  QVBoxLayout *vlayoutTest=new QVBoxLayout(wpid);
  QLabel *title=new QLabel(tr("PID controller"),wpid);
  title->setObjectName("label_currentTitle");
  title->setAlignment(Qt::AlignCenter);
  vlayoutTest->addWidget(title);

  QLabel *pgain=new QLabel(tr("P gain(HZ)"));
  pgain->setObjectName("label_currentPgain");
  vlayoutTest->addWidget(pgain);
  QDoubleSpinBox *pedit=new QDoubleSpinBox(wpid);
  d->m_pEdit=pedit;
  pedit->setObjectName("dspinBox_currentPedit");
  pedit->setMinimum(-32768);
  pedit->setMaximum(32767);
  pedit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  vlayoutTest->addWidget(pedit);

  QLabel *igain=new QLabel(tr("I gain(us)"),wpid);
  igain->setObjectName("label_currentIgain");
  vlayoutTest->addWidget(igain);
  QDoubleSpinBox *iedit=new QDoubleSpinBox(wpid);
  d->m_iEdit=iedit;
  iedit->setObjectName("dspinBox_currentIedit");
  iedit->setMinimum(0);
  iedit->setMaximum(2147483647);
  iedit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  vlayoutTest->addWidget(iedit);

  wpid->setLayout(vlayoutTest);

  d->m_UPID=new WidgetItem;
  d->m_UPID->setWidget(wpid,true);
  d->m_UPID->setObjectName("pid");
  d->m_scene->addItem(d->m_UPID);//take ownership

  d->m_widgetItemList.append(d->m_UPID);

}

void IGraphCurrent::createInputFilterItem()
{
  Q_D(IGraphCurrent);
  LabelItemWidget *label=new LabelItemWidget(tr("InputFilter"));
  label->setObjectName("label_currentInputFilter");
  label->setAlignment(Qt::AlignCenter);
  d->m_UIF=new WidgetItem;
  d->m_UIF->setWidget(label,true);
  d->m_UIF->setObjectName("uif");
  d->m_scene->addItem(d->m_UIF);

  d->m_widgetItemList.append(d->m_UIF);
}

void IGraphCurrent::createArrowItems()
{
  Q_D(IGraphCurrent);
  d->m_A0=new ArrowItem(d->m_Tstart->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UIF->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A1=new ArrowItem(d->m_UIF->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_USUM->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A2=new ArrowItem(d->m_USUM->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UPID->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A3=new ArrowItem(d->m_UPID->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_Tend->pointF(WidgetItem::POINT_TYPE_LEFT));
  d->m_A4=new ArrowItem(d->m_T0->pointF(WidgetItem::POINT_TYPE_LEFT),d->m_UCB->pointF(WidgetItem::POINT_TYPE_RIGHT));
  d->m_A5=new ArrowItem(d->m_UCB->pointF(WidgetItem::POINT_TYPE_LEFT),d->m_USUM->pointF(WidgetItem::POINT_TYPE_BOTTOM),ArrowItem::ARROW_TYPE_CORNER,"-");

  d->m_scene->addItem(d->m_A0);
  d->m_scene->addItem(d->m_A1);
  d->m_scene->addItem(d->m_A2);
  d->m_scene->addItem(d->m_A3);
  d->m_scene->addItem(d->m_A4);
  d->m_scene->addItem(d->m_A5);

  d->m_arrowList.append(d->m_A0);
  d->m_arrowList.append(d->m_A1);
  d->m_arrowList.append(d->m_A2);
  d->m_arrowList.append(d->m_A3);
  d->m_arrowList.append(d->m_A4);
  d->m_arrowList.append(d->m_A5);

}

void IGraphCurrent::createCurrentFeedbackItem()
{
  Q_D(IGraphCurrent);
  LabelItemWidget *label=new LabelItemWidget(tr("CurrentFeedback"));
  label->setObjectName("label_currentFeedback");
  label->setAlignment(Qt::AlignCenter);
  d->m_UCB=new WidgetItem;
  d->m_UCB->setWidget(label,true);
  d->m_UCB->setObjectName("ucb");
  d->m_scene->addItem(d->m_UCB);

  d->m_widgetItemList.append(d->m_UCB);
}

void IGraphCurrent::createSumItem()
{
  Q_D(IGraphCurrent);
  SumItemWidget *sw=new SumItemWidget;
  sw->setObjectName("sumItemWidget_currentSum");
  d->m_USUM=new WidgetItem;
  d->m_USUM->setWidget(sw);
  d->m_USUM->setObjectName("USUM");
  d->m_scene->addItem(d->m_USUM);

  d->m_widgetItemList.append(d->m_USUM);
}

void IGraphCurrent::setUpItemPosAnchors()
{
  Q_D(IGraphCurrent);
  d->m_UPID->setPos(PID_POS_X,PID_POS_Y);
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_USUM,AnchorItemHelper::AnchorLeft,-3*d->m_USUM->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_USUM,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_USUM,d->m_UIF,AnchorItemHelper::AnchorRight,-3*d->m_USUM->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_USUM,d->m_UIF,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UIF,d->m_Tstart,AnchorItemHelper::AnchorLeft,-1.5*d->m_UIF->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UIF,d->m_Tstart,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_UCB,AnchorItemHelper::AnchorHorizontalCenter);
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_UCB,AnchorItemHelper::AnchorBottom,2.2*d->m_UCB->boundingRect().height());

  d->m_anchorHelper->addAnchor(d->m_UCB,d->m_T0,AnchorItemHelper::AnchorRight,1*d->m_UCB->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UCB,d->m_T0,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_Tend,AnchorItemHelper::AnchorRight,1.5*d->m_UPID->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_Tend,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_Tstart,d->m_TextStart,AnchorItemHelper::AnchorLeft,1.2*d->m_Tstart->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_Tstart,d->m_TextStart,AnchorItemHelper::AnchorBottom,-15);

  d->m_anchorHelper->addAnchor(d->m_Tend,d->m_TextEnd,AnchorItemHelper::AnchorRight,-1.2*d->m_Tend->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_Tend,d->m_TextEnd,AnchorItemHelper::AnchorBottom,-15);

}

void IGraphCurrent::createStartEndTargetItems()
{
  Q_D(IGraphCurrent);
  TargetItemWidget *t0=new TargetItemWidget;
  t0->setObjectName("targetItem_currentTstart");
  d->m_Tstart=new WidgetItem;
  d->m_Tstart->setWidget(t0);
  d->m_Tstart->setObjectName("Tstart");

  t0=new TargetItemWidget;
  t0->setObjectName("targetItem_currentTend");
  d->m_Tend=new WidgetItem;
  d->m_Tend->setWidget(t0);
  d->m_Tend->setObjectName("Tend");

  d->m_scene->addItem(d->m_Tstart);
  d->m_scene->addItem(d->m_Tend);

  d->m_widgetItemList.append(d->m_Tstart);
  d->m_widgetItemList.append(d->m_Tend);
}

void IGraphCurrent::createCurrentFeedbackTargetItem()
{
  Q_D(IGraphCurrent);
  TargetItemWidget *t0=new TargetItemWidget;
  t0->setObjectName("targetItem_currentT0");
  d->m_T0=new WidgetItem;
  d->m_T0->setWidget(t0);
  d->m_T0->setObjectName("T0");
  d->m_scene->addItem(d->m_T0);

  d->m_widgetItemList.append(d->m_T0);
}

void IGraphCurrent::createAnchorItemHelper()
{
  Q_D(IGraphCurrent);
  d->m_anchorHelper=new AnchorItemHelper(this);
}

void IGraphCurrent::createStartTextItem()
{
  Q_D(IGraphCurrent);

  LabelItemWidget *label=new LabelItemWidget(tr("cur/torque cmd"));
  label->setObjectName("label_currentStartText");
  d->m_TextStart=new WidgetItem;
  d->m_TextStart->setWidget(label);
  d->m_TextStart->setObjectName("StartText");
  d->m_scene->addItem(d->m_TextStart);

  d->m_widgetItemList.append(d->m_TextStart);
}

void IGraphCurrent::createEndTextItem()
{
  Q_D(IGraphCurrent);

  LabelItemWidget *label=new LabelItemWidget(tr("cur/torque controller output"));
  label->setObjectName("label_currentEndText");
  label->setAlignment(Qt::AlignRight);
  d->m_TextEnd=new WidgetItem;
  d->m_TextEnd->setWidget(label);
  d->m_TextEnd->setObjectName("EndText");
  d->m_scene->addItem(d->m_TextEnd);

  d->m_widgetItemList.append(d->m_TextEnd);
}


void IGraphCurrent::createItems()
{
  //create所有的item
  //create Arrows
  //create定位器
  //安排定位
  //更新位置
  createPidControllerItem();
  createSumItem();
  createInputFilterItem();
  createStartEndTargetItems();
  createCurrentFeedbackItem();
  createCurrentFeedbackTargetItem();
  createStartTextItem();
  createEndTextItem();

  createArrowItems();

  createAnchorItemHelper();
  setUpItemPosAnchors();

  adjustPosition();
  setCustumBackgroundColor();
}


void IGraphCurrent::installDoubleSpinBoxEventFilter()
{
  Q_D(IGraphCurrent);
  d->m_pEdit->installEventFilter(this);
  d->m_iEdit->installEventFilter(this);
}

void IGraphCurrent::setDoubleSpinBoxConnections()
{
  Q_D(IGraphCurrent);
  connect(d->m_pEdit,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_iEdit,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
}


void IGraphCurrent::adjustPosition()
{
  Q_D(IGraphCurrent);

  GTUtils::delayms(10);

  if(d->m_anchorHelper!=NULL)
    d->m_anchorHelper->setAnchorsActive();

  GTUtils::delayms(10);
  foreach (ArrowItem *arrow, d->m_arrowList) {
    arrow->updatePosition();
    arrow->setColor(arrowColor());
  }
}


IGraphCurrent::IGraphCurrent(IGraphCurrentPrivate &dd, QWidget *parent):IGraphWidget(dd,parent)
{

}
