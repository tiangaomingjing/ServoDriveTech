#include "graphvelocity133.h"
#include "igraphvelocity_p.h"
#include "boxitemmapping.h"
#include "widgetitem.h"
#include "velpid133.h"
#include "sevdevice.h"
#include "deviceconfig.h"
#include "iuiwidget.h"

#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QLabel>
#include <QVBoxLayout>
#include <QDoubleSpinBox>

#define MOT_NOS_KEY_NAME "gSevDrv.sev_obj.cur.mot.Nos_1"
#define POW2_24 16777216

#define PID_POS_X -100
#define PID_POS_Y -240

#define FN_FST_5_INX      0
#define TI_FST_5_INX      1
#define ABS_RAT_5_INX     2
#define POS_RAT_5_INX     3
#define NEG_RAT_5_INX     4
#define FN_SEC_5_INX      5
#define TI_SEC_5_INX      6
#define KVI_SW_EN_INX     7
#define KVI_SW_TIM_INX    8
#define KVI_SW_SPDU_INX   9
#define KVI_SW_SPDL_INX   10

class GraphVelocity133Private:public IGraphVelocityPrivate
{
  Q_DECLARE_PUBLIC(GraphVelocity133)
public:
  GraphVelocity133Private(){}
  ~GraphVelocity133Private(){}

protected:
  VelPid133 *m_pid133;

};

GraphVelocity133::GraphVelocity133(QWidget *parent) :
  IGraphVelocity(*(new GraphVelocity133Private),parent)
{
}

GraphVelocity133::~GraphVelocity133()
{
//  delete ui;
  qDebug()<<"GraphVelocity133 destruct-->";
}
void GraphVelocity133::setCustomVisitActive(IUiWidget *uiWidget)
{
  Q_UNUSED(uiWidget);
}
void GraphVelocity133::setUiVersionName()
{
  Q_D(GraphVelocity133);
  d->m_versionName="V133";
  setObjectName("GraphVelocity133");
}

void GraphVelocity133::setupDataMappings()
{
  Q_D(GraphVelocity133);

  d->m_mapping->insertBox2Item(d->m_pEdit,d->m_treeWidget->topLevelItem(FN_FST_5_INX));
  d->m_mapping->insertBox2Item(d->m_iEdit,d->m_treeWidget->topLevelItem(TI_FST_5_INX));

  d->m_mapping->insertBox2Item(d->m_maxTqEdit,d->m_treeWidget->topLevelItem(ABS_RAT_5_INX));
  d->m_mapping->insertBox2Item(d->m_maxTqEdit_P,d->m_treeWidget->topLevelItem(POS_RAT_5_INX));
  d->m_mapping->insertBox2Item(d->m_maxTqEdit_N,d->m_treeWidget->topLevelItem(NEG_RAT_5_INX));


  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(FN_FST_5_INX),d->m_pEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(TI_FST_5_INX),d->m_iEdit);

  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(ABS_RAT_5_INX),d->m_maxTqEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(POS_RAT_5_INX),d->m_maxTqEdit_P);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(NEG_RAT_5_INX),d->m_maxTqEdit_N);

  //sec pid
  d->m_mapping->insertBox2Item(d->m_pid133->boxP2(),d->m_treeWidget->topLevelItem(FN_SEC_5_INX));
  d->m_mapping->insertBox2Item(d->m_pid133->boxI2(),d->m_treeWidget->topLevelItem(TI_SEC_5_INX));
  d->m_mapping->insertBox2Item(d->m_pid133->boxTime(),d->m_treeWidget->topLevelItem(KVI_SW_TIM_INX));
  d->m_mapping->insertBox2Item(d->m_pid133->boxSpdu(),d->m_treeWidget->topLevelItem(KVI_SW_SPDU_INX));
  d->m_mapping->insertBox2Item(d->m_pid133->boxSpdl(),d->m_treeWidget->topLevelItem(KVI_SW_SPDL_INX));

  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(FN_SEC_5_INX),d->m_pid133->boxP2());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(TI_SEC_5_INX),d->m_pid133->boxI2());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(KVI_SW_TIM_INX),d->m_pid133->boxTime());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(KVI_SW_SPDU_INX),d->m_pid133->boxSpdu());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(KVI_SW_SPDL_INX),d->m_pid133->boxSpdl());

}

void GraphVelocity133::createPidItem()
{
  Q_D(GraphVelocity133);

  QWidget *wout = new QWidget;
  QVBoxLayout *voutLayout = new QVBoxLayout(wout);
  QSpacerItem *verticalSpacer1 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  QSpacerItem *verticalSpacer2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

  QWidget *w = new QWidget;
  w->setObjectName("widget_velPid");
  QVBoxLayout *vlayout = new QVBoxLayout(w);

  d->m_pid133 = new VelPid133(w);
  connect(d->m_pid133,SIGNAL(comboBoxIndexChanged(int)),this,SLOT(onPidComboBoxSWIndexChanged(int)));
  vlayout->addWidget(d->m_pid133);
  w->setLayout(vlayout);

  voutLayout->addSpacerItem(verticalSpacer1);
  voutLayout->addWidget(w);
  voutLayout->addSpacerItem(verticalSpacer2);
  voutLayout->setContentsMargins(0,0,0,0);
  wout->setLayout(voutLayout);

  d->m_pEdit=d->m_pid133->boxP1();//p1
  d->m_iEdit=d->m_pid133->boxI1();//i1


  d->m_UPID=new WidgetItem;
  d->m_UPID->setWidget(wout,true);
  d->m_scene->addItem(d->m_UPID);//take ownership

  d->m_widgetItemList.append(d->m_UPID);
}

void GraphVelocity133::onPidComboBoxSWIndexChanged(int index)
{
  Q_D(GraphVelocity133);

  d->m_treeWidget->topLevelItem(KVI_SW_EN_INX)->setText(GT::COL_PAGE_TREE_VALUE,QString::number(index));
  qDebug()<<"velocity index = "<<index;
}

QPointF GraphVelocity133::pidInitPos()
{
  return QPointF(PID_POS_X,PID_POS_Y);
}
quint16 GraphVelocity133::readNos(const QString &key)
{
  Q_D(GraphVelocity133);
  bool isOk=true;
  quint16 nos=0;
  nos=d->m_dev->genCmdRead(key,d->m_uiWidget->uiIndexs().axisInx,isOk);
  return nos;
}

void GraphVelocity133::syncTreeDataToUiFace()
{
  Q_D(GraphVelocity133);

  //读变量，修改动态增益
  quint16 nos = readNos(MOT_NOS_KEY_NAME);
  if(nos == 0)
    nos = 1;
  double n = nos;
  double k = POW2_24/n;
  d->m_treeWidget->topLevelItem(KVI_SW_SPDU_INX)->setText(GT::COL_PAGE_TREE_SCALE,QString::number(k,'f',3));
  d->m_treeWidget->topLevelItem(KVI_SW_SPDL_INX)->setText(GT::COL_PAGE_TREE_SCALE,QString::number(k,'f',3));

  IGraphVelocity::syncTreeDataToUiFace();

  quint16 sw_en = d->m_treeWidget->topLevelItem(KVI_SW_EN_INX)->text(GT::COL_PAGE_TREE_VALUE).toUShort();
  d->m_pid133->setCurrentPidSegment(sw_en);

  qDebug()<<"sw_en = "<<sw_en;

}

void GraphVelocity133::installDoubleSpinBoxEventFilter()
{
  Q_D(GraphVelocity133);
  IGraphVelocity::installDoubleSpinBoxEventFilter();

  d->m_pid133->boxI2()->installEventFilter(this);
  d->m_pid133->boxP2()->installEventFilter(this);
  d->m_pid133->boxTime()->installEventFilter(this);
  d->m_pid133->boxSpdl()->installEventFilter(this);
  d->m_pid133->boxSpdu()->installEventFilter(this);
}
void GraphVelocity133::setDoubleSpinBoxConnections()
{
  Q_D(GraphVelocity133);
  IGraphVelocity::setDoubleSpinBoxConnections();
//  connect(d->m_pEdit,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_pid133->boxI2(),SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_pid133->boxP2(),SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_pid133->boxTime(),SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_pid133->boxSpdl(),SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_pid133->boxSpdu(),SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
}
