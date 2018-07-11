#include "nolinearcontroller133.h"
#include "NodeItems.h"
#include "labelitemwidget.h"
#include "saturationitemwidget.h"
#include "kuselectwidget133.h"
#include "sumitemwidget.h"
#include "boxitemmapping.h"
#include "frameitemwidget.h"

#include <QGraphicsView>
#include <QDebug>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGraphicsSimpleTextItem>
#include <QPushButton>
#include <QProgressBar>

NolinearController133::NolinearController133(QGraphicsView *view, QObject *parent) : QObject(parent),
  m_view(view)
{
  createDirItem();
  createInputFilterItem();
  createCurrentItem();
  createAccItem();
  createSaturationItem();
  createKdItem();
  createKpItem();
  createKiItem();
  createKnItem();
  createKuSelItem();
  createStartItem();
  createEndItem();
  createSumItem();
  createMidPortItem();
  createSwitchItem();
  createANVSFreqItem();
  createANVSGainItem();
  createFeedBackItem();
  createSaturationConfigItem();
  createAutoTurningItem();

  createArrowsItem();
  resetAllItemParent();
  adjustPostion();

  onSaturationClicked(false);

  m_boxItemMapping = new BoxItemMapping;
}

NolinearController133::~NolinearController133()
{
  delete m_boxItemMapping;
}

void NolinearController133::adjustPostion()
{
  m_dirItem->setPos(80,-(m_dirItem->boundingRect().height()/2-m_startPort->rect().height()/2));
  m_inputFilterItem->setPos(m_dirItem->boundingRect().width()+20,-(m_inputFilterItem->boundingRect().height()-m_dirItem->boundingRect().height())/2);
  m_midPort1->setPos(m_inputFilterItem->boundingRect().width()+15,-(m_midPort1->rect().height()-m_inputFilterItem->boundingRect().height())/2);
  m_sum1Item->setPos(m_midPort1->boundingRect().width()+15,-(m_sum1Item->boundingRect().height()-m_midPort1->boundingRect().height())/2);
  m_midPort2->setPos(m_sum1Item->boundingRect().width()+30,-(m_midPort2->rect().height()-m_sum1Item->boundingRect().height())/2);
  m_kpItem->setPos(m_midPort2->boundingRect().width()+30,-m_kpItem->boundingRect().height()-15);
  m_kdItem->setPos(0,-m_kdItem->boundingRect().height()-30);
  m_accItem->setPos(0,-m_accItem->boundingRect().height()-30);
  m_kiItem->setPos(m_midPort2->boundingRect().width()+30,15);
  m_knItem->setPos(0,m_kiItem->boundingRect().height()+30);
  m_midPort3->setPos(m_kpItem->pos().x()+m_kpItem->boundingRect().width()+30,0);
  m_kuSelectItem->setPos(m_midPort3->rect().width()+30,-(m_kuSelectItem->boundingRect().height()-m_midPort3->rect().height())/2);
  m_sum2Item->setPos(m_kuSelectItem->boundingRect().width()+30,-(m_sum2Item->boundingRect().height()-m_kuSelectItem->boundingRect().height())/2);
  m_saturationItem->setPos(m_sum2Item->boundingRect().width()+30,-(m_saturationItem->boundingRect().height()-m_sum2Item->rect().height())/2);
  m_currentCtlerItem->setPos(m_saturationItem->boundingRect().width()+30,-(m_currentCtlerItem->boundingRect().height()-m_saturationItem->boundingRect().height())/2);
  m_endPort->setPos(m_currentCtlerItem->boundingRect().width()+30,-(m_endPort->rect().height()-m_currentCtlerItem->boundingRect().height())/2);

  QPointF p1 = m_sum1Item->mapFromItem(m_knItem,QPointF(0,m_knItem->boundingRect().height()));
  m_midPort4->setPos((m_sum1Item->rect().width()-m_midPort4->rect().width())/2,p1.y()+m_anvsFreqItem->boundingRect().height()/2+30);
  m_swItem->setPos(m_midPort4->rect().width()+40,-(m_swItem->boundingRect().height()-m_midPort4->rect().height())/2);
  m_anvsFreqItem->setPos(m_swItem->boundingRect().width()+30,-(m_anvsFreqItem->boundingRect().height()-m_swItem->boundingRect().height())/2-10);
  m_anvsKgItem->setPos(m_anvsFreqItem->boundingRect().width()+30,-(m_anvsKgItem->boundingRect().height()-m_anvsFreqItem->boundingRect().height())/2);

  m_midPortNULL->setPos(m_anvsFreqItem->boundingRect().width()/2-m_midPortNULL->rect().width()/2,m_anvsFreqItem->boundingRect().height()+m_midPortNULL->rect().height()+10);
  m_posFBItem->setPos(0,m_midPortNULL->rect().height()+20);
  m_midPortFB->setPos(m_posFBItem->boundingRect().width()+100,-(m_midPortFB->boundingRect().height()-m_posFBItem->boundingRect().height())/2);

  m_autoTnItem->setPos(-(m_autoTnItem->boundingRect().width()-m_dirItem->boundingRect().width())/2,m_dirItem->boundingRect().height()+100);
}

void NolinearController133::setPos(const QPointF &p)
{
  m_startPort->setPos(p);
  QPointF saturationP = m_saturationItem->scenePos();
  m_satnFrame->setPos(saturationP+QPointF(-(m_satnFrame->boundingRect().width()-m_saturationItem->boundingRect().width())/2,m_saturationItem->boundingRect().height()+5));
}

void NolinearController133::setPos(qreal x, qreal y)
{
  m_startPort->setPos(x,y);
  QPointF saturationP = m_saturationItem->scenePos();
  m_satnFrame->setPos(saturationP+QPointF(-(m_satnFrame->boundingRect().width()-m_saturationItem->boundingRect().width())/2,m_saturationItem->boundingRect().height()+5));
}

QDoubleSpinBox *NolinearController133::boxAcc()
{
  return m_boxAcc;
}

QDoubleSpinBox *NolinearController133::boxKd()
{
  return m_boxKd;
}

QDoubleSpinBox *NolinearController133::boxKi()
{
  return m_boxKi;
}

QDoubleSpinBox *NolinearController133::boxKp()
{
  return m_boxKp;
}

QDoubleSpinBox *NolinearController133::boxKn()
{
  return m_boxKn;
}

QDoubleSpinBox *NolinearController133::boxFn()
{
  return m_boxANVSFn;
}

QDoubleSpinBox *NolinearController133::boxQx()
{
  return m_boxANVSQx;
}

QDoubleSpinBox *NolinearController133::boxKavToPeer()
{
  return m_boxANVSKg;
}

QDoubleSpinBox *NolinearController133::boxKu1()
{
  return m_kuSelectWidget->boxKu1();
}

QDoubleSpinBox *NolinearController133::boxKu2()
{
  return m_kuSelectWidget->boxKu2();
}

QDoubleSpinBox *NolinearController133::boxTs()
{
  return m_kuSelectWidget->boxTs();
}

QDoubleSpinBox *NolinearController133::boxSpdu()
{
  return m_kuSelectWidget->boxSpdu();
}

QDoubleSpinBox *NolinearController133::boxSpdl()
{
  return m_kuSelectWidget->boxSpdl();
}

QDoubleSpinBox *NolinearController133::boxSatnAbs()
{
  return m_boxSatnAbs;
}

QDoubleSpinBox *NolinearController133::boxSatnPos()
{
  return m_boxSatnPos;
}

QDoubleSpinBox *NolinearController133::boxSatnNeg()
{
  return m_boxSatnNeg;
}

QDoubleSpinBox *NolinearController133::boxMotionAcc()
{
  return m_boxAutoTnAcc;
}

QDoubleSpinBox *NolinearController133::boxMotionDec()
{
  return m_boxAutoTnDec;
}

QDoubleSpinBox *NolinearController133::boxMotionMaxSpd()
{
  return m_boxAutoTnMaxVel;
}

QDoubleSpinBox *NolinearController133::boxMotionPos()
{
  return m_boxAutoTnPulseNum;
}

void NolinearController133::setDir(int dir)
{
  if(dir == 0)
    m_cwRBtn->setChecked(true);
  else
    m_cwRBtn->setChecked(false);
}

void NolinearController133::setCurrentKuMode(int mode)
{
  m_kuSelectWidget->setKuModeUi(mode);
}

void NolinearController133::setSwON(bool on)
{
  m_swItem->setIsOn(on);
}

void NolinearController133::onRadioBtnClicked()
{
  int dir = 0;
  if(m_cwRBtn->isChecked())
    dir = 0;
  else
    dir = 1;
  emit dirChanged(dir);

}

void NolinearController133::onSaturationClicked(bool checked)
{
  qDebug()<<"on saturation clicked";
  m_satnFrame->setVisible(checked);
  foreach (INodeConnection *cnn, m_nodeConnectionList) {
    cnn->setVisible(checked);
  }

}

void NolinearController133::onBtnAutoStartClicked(bool checked)
{
  if(checked)
  {
    m_btnAutoStart->setText(tr("auto turning stop"));
    m_bar->setVisible(true);
  }
  else
  {
    m_btnAutoStart->setText(tr("auto turning start"));
    m_bar->setVisible(false);
  }
  emit btnAutoStartClicked(checked);
}
void NolinearController133::createDirItem()
{
  m_dirItem = new NodeBlock;
  QWidget *posWidget = new QWidget;
  posWidget->setObjectName("widget_posDir");
  QVBoxLayout *vlayout = new QVBoxLayout(posWidget);
  QLabel *label = new QLabel(tr("DirCtl"),posWidget);
  label->setAlignment(Qt::AlignCenter);
  label->setObjectName("label_posDirControl");
  QHBoxLayout *hlayout = new QHBoxLayout;
  m_cwRBtn = new QRadioButton(posWidget);
  m_cwRBtn->setText(tr("CW"));
  m_cwRBtn->setChecked(true);
  m_ccwRBtn = new QRadioButton(posWidget);
  m_ccwRBtn->setText(tr("CCW"));
  m_ccwRBtn->setChecked(false);
  connect(m_cwRBtn,SIGNAL(clicked(bool)),this,SLOT(onRadioBtnClicked()));
  connect(m_ccwRBtn,SIGNAL(clicked(bool)),this,SLOT(onRadioBtnClicked()));
  hlayout->addWidget(m_cwRBtn);
  hlayout->addWidget(m_ccwRBtn);
  vlayout->addWidget(label);
  vlayout->addLayout(hlayout);
  posWidget->setLayout(vlayout);
  m_dirItem->setCenterWidget(posWidget,true);

  addItem(m_dirItem);

}

void NolinearController133::createInputFilterItem()
{
  m_inputFilterItem = new NodeBlock;
  LabelItemWidget *label=new LabelItemWidget(tr("InputFilter"));
  label->setObjectName("label_posInputFilter");
  label->setAlignment(Qt::AlignCenter);
  connect(label,SIGNAL(clicked()),this,SIGNAL(inputFilterItemClicked()));
  m_inputFilterItem->setCenterWidget(label,true);

  addItem(m_inputFilterItem);

}

void NolinearController133::createCurrentItem()
{
  m_currentCtlerItem = new NodeBlock;
  LabelItemWidget *label=new LabelItemWidget(tr("CurCtler"));
  label->setObjectName("label_posCurCtler");
  label->setAlignment(Qt::AlignCenter);
  m_currentCtlerItem->setCenterWidget(label,true);

  addItem(m_currentCtlerItem);
}

void NolinearController133::createAccItem()
{
  m_accItem = new NodeBlock;
  QWidget *w=new QWidget;
  w->setObjectName("widget_posFFacc");
  QVBoxLayout *vlayoutTest=new QVBoxLayout(w);

  QLabel *label=new QLabel(tr("acceleration feedforward (%)"));
  label->setObjectName("label_posFFacc");
  vlayoutTest->addWidget(label);
  m_boxAcc=new QDoubleSpinBox(w);
  m_boxAcc->setMinimum(0);
  m_boxAcc->setMaximum(32767);
  m_boxAcc->setObjectName("dspinBox_posFFacc2");
  m_boxAcc->setButtonSymbols(QAbstractSpinBox::NoButtons);
  vlayoutTest->addWidget(m_boxAcc);
  w->setLayout(vlayoutTest);

  m_accItem->setCenterWidget(w,true);

  addItem(m_accItem);

}

void NolinearController133::createSaturationItem()
{
  m_saturationItem = new NodeBlock;
  QWidget *w=new QWidget;
  w->setObjectName("widget_posSaturation");
  QVBoxLayout *vlayout=new QVBoxLayout(w);
  vlayout->setMargin(2);
  SaturationItemWidget *saturation=new SaturationItemWidget(w);
  connect(saturation,SIGNAL(clicked(bool)),this,SLOT(onSaturationClicked(bool)));
  saturation->setObjectName("saturationItemWidget_posSaturation");
  vlayout->addWidget(saturation);
  w->setLayout(vlayout);

  m_saturationItem->setCenterWidget(w,true);

  addItem(m_saturationItem);
}

void NolinearController133::createSaturationConfigItem()
{
  m_satnFrame = new NodeBlock;
  FrameItemWidget *frame=new FrameItemWidget;
  frame->setWPercent(0.1);
  frame->setMinimumSize(600,250);
  frame->setObjectName("frameItemWidget_posFrameVel");
  m_satnFrame->setCenterWidget(frame);


  //max vel %
  m_satnAbs = new NodeBlock;
  QWidget *w=new QWidget;
  w->setObjectName("widget_posMaxVel");
  QVBoxLayout *hlayout=new QVBoxLayout(w);
  QLabel *label=new QLabel(tr("max v(%)"),w);
  label->setObjectName("label_posMaxVelPercent");
  hlayout->addWidget(label);
  QDoubleSpinBox *box=new QDoubleSpinBox(w);
  m_boxSatnAbs=box;
  box->setMinimum(0);
  box->setMaximum(32767);
  box->setMaximumWidth(150);
  box->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(box);
  w->setLayout(hlayout);
  m_satnAbs->setCenterWidget(w);

  //max vel_p %
  m_satnPos = new NodeBlock;
  w=new QWidget;
  w->setObjectName("widget_posMaxVelPositive");
  hlayout=new QVBoxLayout(w);
  label=new QLabel(tr("positive v(%)"),w);
  label->setObjectName("label_posMaxVelPercentPositive");
  hlayout->addWidget(label);
  box=new QDoubleSpinBox(w);
  m_boxSatnPos=box;
  box->setMinimum(0);
  box->setMaximum(32767);
  box->setMaximumWidth(150);
  box->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(box);
  w->setLayout(hlayout);
  m_satnPos->setCenterWidget(w);


  //max vel_n %
  m_satnNeg = new NodeBlock;
  w=new QWidget;
  w->setObjectName("widget_posMaxVelNegative");
  hlayout=new QVBoxLayout(w);
  label=new QLabel(tr("negative v(%)"),w);
  label->setObjectName("label_posMaxVelPercentNegative");
  hlayout->addWidget(label);
  box=new QDoubleSpinBox(w);
  m_boxSatnNeg=box;
  box->setMinimum(0);
  box->setMaximum(32767);
  box->setMaximumWidth(150);
  box->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(box);
  w->setLayout(hlayout);
  m_satnNeg->setCenterWidget(w);


  NodePort *pMid = new NodePort;
  NodePort *pPos = new NodePort;
  NodePort *pNeg = new NodePort;


  m_satnNeg->setParentItem(m_satnFrame);
  m_satnAbs->setParentItem(m_satnFrame);
  m_satnPos->setParentItem(m_satnNeg);
  pMid->setParentItem(m_satnAbs);
  pPos->setParentItem(m_satnPos);
  pNeg->setParentItem(m_satnNeg);

  m_satnAbs->setPos(40,-(m_satnAbs->boundingRect().height()-m_satnFrame->boundingRect().height())/2+40);
  m_satnNeg->setPos(m_satnFrame->boundingRect().width()-(m_satnPos->boundingRect().width()+230),m_satnFrame->boundingRect().height()-m_satnNeg->boundingRect().height()-10);
  m_satnPos->setPos(0,-m_satnPos->boundingRect().height()-10);

  pMid->setPos(m_satnAbs->boundingRect().width()+20,-(pMid->boundingRect().height()-m_satnAbs->boundingRect().height())/2);
  pPos->setPos(m_satnPos->boundingRect().width()+20,-(pPos->boundingRect().height()-m_satnPos->boundingRect().height())/2);
  pNeg->setPos(m_satnNeg->boundingRect().width()+20,-(pNeg->boundingRect().height()-m_satnNeg->boundingRect().height())/2);

  QGraphicsSimpleTextItem *text1 = new QGraphicsSimpleTextItem(pPos);
  QGraphicsSimpleTextItem *text2 = new QGraphicsSimpleTextItem(pNeg);
  text1->setText(tr("pos max"));
  text2->setText(tr("neg max"));
  text1->setPos(5,-(text1->boundingRect().height()-pPos->boundingRect().height())/2);
  text2->setPos(5,-(text2->boundingRect().height()-pNeg->boundingRect().height())/2);

  NodeLine *L1 = new NodeLine(m_satnAbs->rightPort(),pMid,INodeConnection::DIR_DOWN,false);
  NodeCornerLine *L2 = new NodeCornerLine(pMid,m_satnPos->leftPort(),INodeConnection::DIR_UP);
  NodeCornerLine *L3 = new NodeCornerLine(pMid,m_satnNeg->leftPort(),INodeConnection::DIR_DOWN);
  NodeLine *L4 = new NodeLine(m_satnPos->rightPort(),pPos);
  NodeLine *L5 = new NodeLine(m_satnNeg->rightPort(),pNeg);


  m_satnFrame->setZValue(101);
  m_satnAbs->setZValue(101);
  m_satnNeg->setZValue(101);
  m_satnPos->setZValue(101);
  pMid->setZValue(101);
  pPos->setZValue(101);
  pNeg->setZValue(101);
  text1->setZValue(101);
  text2->setZValue(101);
  L1->setZValue(101);
  L2->setZValue(101);
  L3->setZValue(101);
  L4->setZValue(101);
  L5->setZValue(101);
  m_nodeConnectionList<<L1<<L2<<L3<<L4<<L5;

  addItem(m_satnFrame);
  addItem(m_satnAbs);
  addItem(m_satnPos);
  addItem(m_satnNeg);
  addItem(pMid);
  addItem(pPos);
  addItem(pNeg);
  addItem(L1);
  addItem(L2);
  addItem(L3);
  addItem(L4);
  addItem(L5);
  addItem(text1);
  addItem(text2);

}

void NolinearController133::createAutoTurningItem()
{
  m_autoTnItem = new NodeBlock;
  QWidget *w = new QWidget;
  w->setObjectName("widget_nolinearCtl_autoTurning");
  QVBoxLayout *vlayout = new QVBoxLayout(w);
  QFormLayout *flayout = new QFormLayout();
  QLabel *label = new QLabel(tr("AutoTurning"),w);
  label->setAlignment(Qt::AlignCenter);
  label->setObjectName("label_nolinearCtl_autoTurning");
  m_boxAutoTnAcc = new QDoubleSpinBox(w);
  m_boxAutoTnAcc->setMinimum(0);
  m_boxAutoTnAcc->setMaximum(32767);
  m_boxAutoTnAcc->setButtonSymbols(QAbstractSpinBox::NoButtons);
  m_boxAutoTnDec = new QDoubleSpinBox(w);
  m_boxAutoTnDec->setMinimum(0);
  m_boxAutoTnDec->setMaximum(32767);
  m_boxAutoTnDec->setButtonSymbols(QAbstractSpinBox::NoButtons);
  m_boxAutoTnMaxVel = new QDoubleSpinBox(w);
  m_boxAutoTnMaxVel->setMinimum(0);
  m_boxAutoTnMaxVel->setMaximum(32767);
  m_boxAutoTnMaxVel->setButtonSymbols(QAbstractSpinBox::NoButtons);
  m_boxAutoTnPulseNum = new QDoubleSpinBox(w);
  m_boxAutoTnPulseNum->setMinimum(0);
  m_boxAutoTnPulseNum->setMaximum(32767);
  m_boxAutoTnPulseNum->setButtonSymbols(QAbstractSpinBox::NoButtons);
  m_bar = new QProgressBar(w);
  m_bar->setValue(0);
  m_bar->setMaximum(100);
  m_bar->setVisible(false);
  m_btnAutoStart = new QPushButton(w);
  connect(m_btnAutoStart,SIGNAL(clicked(bool)),this,SLOT(onBtnAutoStartClicked(bool)));
  m_btnAutoStart->setCheckable(true);
  m_btnAutoStart->setText(tr("auto turning start"));
  m_btnAutoStart->setObjectName("btn_nolinearCtl_autoStart");
  flayout->addRow(tr("acc(deg/ms^2)"),m_boxAutoTnAcc);
  flayout->addRow(tr("dec(deg/ms^2)"),m_boxAutoTnDec);
  flayout->addRow(tr("vel(rpm)"),m_boxAutoTnMaxVel);
  flayout->addRow(tr("pos(r)"),m_boxAutoTnPulseNum);
  vlayout->addWidget(label);
  vlayout->addLayout(flayout);
  vlayout->addWidget(m_bar);
  vlayout->addWidget(m_btnAutoStart);
  w->setLayout(vlayout);
  m_autoTnItem->setCenterWidget(w,true);
  addItem(m_autoTnItem);
}

void NolinearController133::createKdItem()
{
  m_kdItem = new NodeBlock;
  QWidget *w=new QWidget;
  w->setObjectName("widget_posKd");
  QHBoxLayout *hlayout=new QHBoxLayout(w);
  QLabel *label = new QLabel(tr("kd(rad/s):"),w);
  m_boxKd = new QDoubleSpinBox(w);
  m_boxKd->setMinimum(0);
  m_boxKd->setMaximum(32767);
  m_boxKd->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(label);
  hlayout->addWidget(m_boxKd);
  w->setLayout(hlayout);

  m_kdItem->setCenterWidget(w,true);

  addItem(m_kdItem);
}

void NolinearController133::createKpItem()
{
  m_kpItem = new NodeBlock;
  QWidget *w=new QWidget;
  w->setObjectName("widget_posKp");
  QHBoxLayout *hlayout=new QHBoxLayout(w);
  QLabel *label = new QLabel(tr("kp(rad/s):"),w);
  m_boxKp = new QDoubleSpinBox(w);
  m_boxKp->setMinimum(0);
  m_boxKp->setMaximum(32767);
  m_boxKp->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(label);
  hlayout->addWidget(m_boxKp);
  w->setLayout(hlayout);

  m_kpItem->setCenterWidget(w,true);

  addItem(m_kpItem);
}

void NolinearController133::createKiItem()
{
  m_kiItem = new NodeBlock;
  QWidget *w=new QWidget;
  w->setObjectName("widget_posKi");
  QHBoxLayout *hlayout=new QHBoxLayout(w);
  QLabel *label = new QLabel(tr("ki(rad/s):"),w);
  m_boxKi = new QDoubleSpinBox(w);
  m_boxKi->setMinimum(0);
  m_boxKi->setMaximum(32767);
  m_boxKi->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(label);
  hlayout->addWidget(m_boxKi);
  w->setLayout(hlayout);

  m_kiItem->setCenterWidget(w,true);

  addItem(m_kiItem);
}

void NolinearController133::createKnItem()
{
  m_knItem = new NodeBlock;
  QWidget *w=new QWidget;
  w->setObjectName("widget_posKn");
  QHBoxLayout *hlayout=new QHBoxLayout(w);
  QLabel *label = new QLabel(tr("kn(rad/s):"),w);
  m_boxKn = new QDoubleSpinBox(w);
  m_boxKn->setMinimum(0);
  m_boxKn->setMaximum(32767);
  m_boxKn->setButtonSymbols(QAbstractSpinBox::NoButtons);
  hlayout->addWidget(label);
  hlayout->addWidget(m_boxKn);
  w->setLayout(hlayout);

  m_knItem->setCenterWidget(w,true);

  addItem(m_knItem);
  m_knItem->setPos(100,-50);
}

void NolinearController133::createKuSelItem()
{
  m_kuSelectItem = new NodeBlock;

  QWidget *wout = new QWidget;
  QPalette p;
  p.setBrush(QPalette::Window,QBrush(Qt::transparent));
  wout->setPalette(p);
  QVBoxLayout *voutLayout = new QVBoxLayout(wout);
  QSpacerItem *verticalSpacer1 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  QSpacerItem *verticalSpacer2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

  QWidget *w = new QWidget;
  w->setObjectName("widget_posPid");
  QVBoxLayout *vlayout = new QVBoxLayout(w);

  m_kuSelectWidget = new KuSelectWidget133;
  connect(m_kuSelectWidget,SIGNAL(kuSwChanged(int)),this,SIGNAL(kuSelectChanged(int)));
  vlayout->addWidget(m_kuSelectWidget);
  w->setLayout(vlayout);

  voutLayout->addSpacerItem(verticalSpacer1);
  voutLayout->addWidget(w);
  voutLayout->addSpacerItem(verticalSpacer2);
  voutLayout->setContentsMargins(0,0,0,0);
  wout->setLayout(voutLayout);

  m_kuSelectItem->setCenterWidget(wout);
  addItem(m_kuSelectItem);
}

void NolinearController133::createStartItem()
{
  m_startPort = new NodePort;
  addItem(m_startPort);
}

void NolinearController133::createEndItem()
{
  m_endPort = new NodePort;
  addItem(m_endPort);
}

void NolinearController133::createSumItem()
{
  m_sum1Item = new NodeBlock;
  m_sum2Item = new NodeBlock;

  SumItemWidget *sum1 = new SumItemWidget;
  SumItemWidget *sum2 = new SumItemWidget;
  m_sum1Item->setCenterWidget(sum1);
  m_sum2Item->setCenterWidget(sum2);
  addItem(m_sum1Item);
  addItem(m_sum2Item);
}

void NolinearController133::createMidPortItem()
{
  m_midPort1 = new NodePort;

  m_midPort2 = new NodePort;

  m_midPort3 = new NodePort;

  m_midPort4 = new NodePort;
  m_midPort4->setRect(0,0,20,20);

  m_midPortNULL = new NodePort;
  m_midPortNULL->setRect(0,0,20,20);

  m_midPortFB = new NodePort;

  addItem(m_midPort1);
  addItem(m_midPort2);
  addItem(m_midPort3);
  addItem(m_midPort4);
  addItem(m_midPortFB);

}

void NolinearController133::createSwitchItem()
{
  m_swItem = new NodeSwitch;
  connect(m_swItem,SIGNAL(clicked(bool)),this,SIGNAL(swChanged(bool)));
  addItem(m_swItem);
}

void NolinearController133::createANVSFreqItem()
{
  m_anvsFreqItem = new NodeBlock;
  QWidget *w=new QWidget;
  w->setObjectName("widget_posANVSFreq");
  QFormLayout *formLayout = new QFormLayout(w);

  m_boxANVSFn=new QDoubleSpinBox(w);
  m_boxANVSFn->setMinimum(0);
  m_boxANVSFn->setMaximum(2147483647);
  m_boxANVSFn->setObjectName("dspinBox_posANVSfn");
  m_boxANVSFn->setButtonSymbols(QAbstractSpinBox::NoButtons);

  m_boxANVSQx=new QDoubleSpinBox(w);
  m_boxANVSQx->setMinimum(0);
  m_boxANVSQx->setMaximum(2147483647);
  m_boxANVSQx->setObjectName("dspinBox_posANVSqx");
  m_boxANVSQx->setButtonSymbols(QAbstractSpinBox::NoButtons);

  formLayout->addRow(tr("fn(HZ)"),m_boxANVSFn);
  formLayout->addRow(tr("qx(0.001)"),m_boxANVSQx);

  w->setLayout(formLayout);

  m_anvsFreqItem->setCenterWidget(w,true);

  addItem(m_anvsFreqItem);
}

void NolinearController133::createANVSGainItem()
{
  m_anvsKgItem = new NodeBlock;
  QWidget *w=new QWidget;
  w->setObjectName("widget_posANVSGain");
  QVBoxLayout *vlayoutTest=new QVBoxLayout(w);

  QLabel *label=new QLabel(tr("kav_to_peer"));
  label->setObjectName("label_posKav_to_peer");
  vlayoutTest->addWidget(label);
  m_boxANVSKg=new QDoubleSpinBox(w);
  m_boxANVSKg->setMinimum(0);
  m_boxANVSKg->setMaximum(32767);
  m_boxANVSKg->setObjectName("dspinBox_posKav_to_peer");
  m_boxANVSKg->setButtonSymbols(QAbstractSpinBox::NoButtons);
  vlayoutTest->addWidget(m_boxANVSKg);
  w->setLayout(vlayoutTest);

  m_anvsKgItem->setCenterWidget(w,true);

  addItem(m_anvsKgItem);
}

void NolinearController133::createFeedBackItem()
{
  m_posFBItem = new NodeBlock;
  LabelItemWidget *label=new LabelItemWidget(tr("PosFeedBack"));
  label->setObjectName("label_posFB");
  label->setAlignment(Qt::AlignCenter);
  m_posFBItem->setCenterWidget(label,true);
  addItem(m_posFBItem);
}

void NolinearController133::createArrowsItem()
{
  NodeLine *L1 = new NodeLine(m_startPort,m_dirItem->leftPort());
  NodeLine *L2 = new NodeLine(m_dirItem->rightPort(),m_inputFilterItem->leftPort(),INodeConnection::DIR_DOWN,false);
  NodeLine *L3 = new NodeLine(m_inputFilterItem->rightPort(),m_midPort1,INodeConnection::DIR_DOWN,false);
  NodeLine *L4 = new NodeLine(m_midPort1,m_sum1Item->leftPort(),INodeConnection::DIR_DOWN,false);
  NodeLine *L5 = new NodeLine(m_sum1Item->rightPort(),m_midPort2,INodeConnection::DIR_DOWN,false);
  NodeCornerLine *L6 = new NodeCornerLine(m_midPort2,m_kpItem->leftPort(),INodeConnection::DIR_UP);
  NodeCornerLine *L7 = new NodeCornerLine(m_midPort2,m_kdItem->leftPort(),INodeConnection::DIR_UP);
  NodeCornerLine *L8 = new NodeCornerLine(m_kdItem->rightPort(),m_midPort3,INodeConnection::DIR_UP,false);
  NodeCornerLine *L9 = new NodeCornerLine(m_kpItem->rightPort(),m_midPort3,INodeConnection::DIR_UP,false);
  NodeCornerLine *L10 = new NodeCornerLine(m_midPort2,m_kiItem->leftPort(),INodeConnection::DIR_DOWN);
  NodeCornerLine *L11 = new NodeCornerLine(m_midPort2,m_knItem->leftPort(),INodeConnection::DIR_DOWN);
  NodeCornerLine *L12 = new NodeCornerLine(m_kiItem->rightPort(),m_midPort3,INodeConnection::DIR_DOWN,false);
  NodeCornerLine *L13 = new NodeCornerLine(m_knItem->rightPort(),m_midPort3,INodeConnection::DIR_DOWN,false);
  NodeCornerLine *L14 = new NodeCornerLine(m_midPort1,m_accItem->leftPort(),INodeConnection::DIR_UP);
  NodeCornerLine *L15 = new NodeCornerLine(m_accItem->rightPort(),m_sum2Item->topPort(),INodeConnection::DIR_UP);
  L15->setText("+");
  NodeLine *L16 = new NodeLine(m_midPort3,m_kuSelectItem->leftPort());
  NodeLine *L17 = new NodeLine(m_kuSelectItem->rightPort(),m_sum2Item->leftPort(),INodeConnection::DIR_DOWN,false);
  NodeLine *L18 = new NodeLine(m_sum2Item->rightPort(),m_saturationItem->leftPort(),INodeConnection::DIR_DOWN,false);
  NodeLine *L19 = new NodeLine(m_saturationItem->rightPort(),m_currentCtlerItem->leftPort(),INodeConnection::DIR_DOWN,false);
  NodeLine *L20 = new NodeLine(m_currentCtlerItem->rightPort(),m_endPort);
  NodeLine *L21 = new NodeLine(m_midPortFB,m_posFBItem->rightPort());
  NodeCornerLine *L22 = new NodeCornerLine(m_posFBItem->leftPort(),m_midPort4,INodeConnection::DIR_DOWN);
  NodeLine *L23 = new NodeLine(m_midPort4,m_sum1Item->bottomPort());
  L23->setText("-");
  NodeLine *L24 = new NodeLine(m_midPort4,m_swItem->leftPort());
  NodeLine *L25 = new NodeLine(m_swItem->topPort(),m_anvsFreqItem->leftPort(),INodeConnection::DIR_DOWN,false);
  NodeLine *L26 = new NodeLine(m_anvsFreqItem->rightPort(),m_anvsKgItem->leftPort(),INodeConnection::DIR_DOWN,false);
  NodeCornerLine *L27 = new NodeCornerLine(m_anvsKgItem->rightPort(),m_sum2Item->bottomPort(),INodeConnection::DIR_DOWN);
  L27->setText("+");
  NodeCornerLine *L28 = new NodeCornerLine(m_swItem->bottomPort(),m_midPortNULL,INodeConnection::DIR_DOWN);
  addItem(L1);
  addItem(L2);
  addItem(L3);
  addItem(L4);
  addItem(L5);
  addItem(L6);
  addItem(L7);
  addItem(L8);
  addItem(L9);
  addItem(L10);
  addItem(L11);
  addItem(L12);
  addItem(L13);
  addItem(L14);
  addItem(L15);
  addItem(L16);
  addItem(L17);
  addItem(L18);
  addItem(L19);
  addItem(L20);
  addItem(L21);
  addItem(L22);
  addItem(L23);
  addItem(L24);
  addItem(L25);
  addItem(L26);
  addItem(L27);
  addItem(L28);
}

void NolinearController133::resetAllItemParent()
{
  m_dirItem->setParentItem(m_startPort);
  m_inputFilterItem->setParentItem(m_dirItem);
  m_midPort1->setParentItem(m_inputFilterItem);
  m_sum1Item->setParentItem(m_midPort1);
  m_midPort2->setParentItem(m_sum1Item);
  m_midPort3->setParentItem(m_midPort2);


  m_kpItem->setParentItem(m_midPort2);
  m_kdItem->setParentItem(m_kpItem);
  m_accItem->setParentItem(m_kdItem);
  m_kiItem->setParentItem(m_midPort2);
  m_knItem->setParentItem(m_kiItem);

  m_kuSelectItem->setParentItem(m_midPort3);
  m_sum2Item->setParentItem(m_kuSelectItem);
  m_saturationItem->setParentItem(m_sum2Item);
  m_currentCtlerItem->setParentItem(m_saturationItem);
  m_endPort->setParentItem(m_currentCtlerItem);

  m_midPort4->setParentItem(m_sum1Item);
  m_swItem->setParentItem(m_midPort4);
  m_anvsFreqItem->setParentItem(m_swItem);
  m_anvsKgItem->setParentItem(m_anvsFreqItem);
  m_midPortNULL->setParentItem(m_anvsFreqItem);
  m_posFBItem->setParentItem(m_midPortNULL);
  m_midPortFB->setParentItem(m_posFBItem);

  m_autoTnItem->setParentItem(m_dirItem);
}

void NolinearController133::addItem(QGraphicsItem *item)
{
  m_view->scene()->addItem(item);
}

BoxItemMapping *NolinearController133::boxItemMapping() const
{
  return m_boxItemMapping;
}

void NolinearController133::setBtnAutoTurningUiOn(bool on)
{
  m_btnAutoStart->setChecked(on);
}

void NolinearController133::setAutoTurningProgressBarValue(int v)
{
  m_bar->setValue(v);
}

void NolinearController133::setProgressBarVisible(bool visible)
{
  m_bar->setVisible(visible);
}

