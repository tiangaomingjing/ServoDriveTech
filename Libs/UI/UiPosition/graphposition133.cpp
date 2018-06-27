#include "graphposition133.h"
#include "igraphposition_p.h"
#include "boxitemmapping.h"
#include "posinputfilter.h"
#include "sevdevice.h"
#include "deviceconfig.h"
#include "iuiwidget.h"
#include "widgetitem.h"
#include "arrowitem.h"
#include "anchoritemhelper.h"
#include "frameitemwidget.h"
#include "pospid133.h"

#include <QTreeWidgetItem>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QDoubleSpinBox>

#define MOT_NOS_KEY_NAME "gSevDrv.sev_obj.cur.mot.Nos_1"
#define POW2_24 16777216

#define PID_POS_X -180
#define PID_POS_Y -100

#define FN_FST_6_INX      0
#define ABS_RAT_6_INX     1
#define POS_RAT_6_INX     2
#define NEG_RAT_6_INX     3
#define KGV_6_INX         4
#define KGA_6_INX         5
#define FN_SEC_6_INX      6
#define MASK_FLAG_INX     7
#define MAF_NUM_INX       8
#define FIT_SEL_INX       9
#define PRM_FN1_INX       10
#define PRM_FN2_INX       11
#define PRM_QX2_INX       12
#define PRM_FN_NCH_INX    13
#define PRM_QX_NCH_INX    14
#define PRM_KN_NCH_INX    15
#define POSR_DIR_INX      16
#define KP_SW_EN_INX      17
#define KP_SW_TIM_INX     18
#define KP_SW_SPDU_INX    19
#define KP_SW_SPDL_INX    20

class GraphPosition133Private:public IGraphPositionPrivate
{
  Q_DECLARE_PUBLIC(GraphPosition133)
public:
  GraphPosition133Private(){}
  ~GraphPosition133Private(){qDebug()<<"GraphPosition133Private destruct-->";}

protected:
  PosInputFilter *m_posInfilter;//输入滤波器对话框

  WidgetItem *m_UPOSDIR;
  QRadioButton *m_cwRBtn;
  QRadioButton *m_ccwRBtn;
  ArrowItem *m_A16;
  PosPID133 *m_pid133;
};

GraphPosition133::GraphPosition133(QWidget *parent) :
  IGraphPosition(*(new GraphPosition133Private),parent)

{
  Q_D(GraphPosition133);
  d->m_posInfilter = new PosInputFilter;
  connect(d->m_posInfilter,SIGNAL(configClicked()),this,SLOT(onFilterConfigClicked()));
  connect(d->m_posInfilter,SIGNAL(saveClicked()),this,SLOT(onFilterSaveClicked()));
}

GraphPosition133::~GraphPosition133()
{

  qDebug()<<"GraphPosition133 destruct-->";
  Q_D(GraphPosition133);

  delete d->m_posInfilter;

}
void GraphPosition133::setCustomVisitActive(IUiWidget *uiWidget)
{
  Q_UNUSED(uiWidget);
}

void GraphPosition133::setupDataMappings()
{
  Q_D(GraphPosition133);

  d->m_mapping->insertBox2Item(d->m_pEdit,d->m_treeWidget->topLevelItem(FN_FST_6_INX));
  d->m_mapping->insertBox2Item(d->m_accEdit,d->m_treeWidget->topLevelItem(KGA_6_INX));
  d->m_mapping->insertBox2Item(d->m_velEdit,d->m_treeWidget->topLevelItem(KGV_6_INX));

  d->m_mapping->insertBox2Item(d->m_maxvelEdit,d->m_treeWidget->topLevelItem(ABS_RAT_6_INX));
  d->m_mapping->insertBox2Item(d->m_maxvelEdit_P,d->m_treeWidget->topLevelItem(POS_RAT_6_INX));
  d->m_mapping->insertBox2Item(d->m_maxvelEdit_N,d->m_treeWidget->topLevelItem(NEG_RAT_6_INX));

  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(FN_FST_6_INX),d->m_pEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(KGA_6_INX),d->m_accEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(KGV_6_INX),d->m_velEdit);

  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(ABS_RAT_6_INX),d->m_maxvelEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(POS_RAT_6_INX),d->m_maxvelEdit_P);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(NEG_RAT_6_INX),d->m_maxvelEdit_N);

  //filter
  d->m_mapping->insertBox2Item(d->m_posInfilter->boxFn1(),d->m_treeWidget->topLevelItem(PRM_FN1_INX));
  d->m_mapping->insertBox2Item(d->m_posInfilter->boxFn2(),d->m_treeWidget->topLevelItem(PRM_FN2_INX));
  d->m_mapping->insertBox2Item(d->m_posInfilter->boxQx2(),d->m_treeWidget->topLevelItem(PRM_QX2_INX));
  d->m_mapping->insertBox2Item(d->m_posInfilter->boxFnNch(),d->m_treeWidget->topLevelItem(PRM_FN_NCH_INX));
  d->m_mapping->insertBox2Item(d->m_posInfilter->boxQxNch(),d->m_treeWidget->topLevelItem(PRM_QX_NCH_INX));
  d->m_mapping->insertBox2Item(d->m_posInfilter->boxKnNch(),d->m_treeWidget->topLevelItem(PRM_KN_NCH_INX));
  d->m_mapping->insertBox2Item(d->m_posInfilter->boxMafNum(),d->m_treeWidget->topLevelItem(MAF_NUM_INX));

  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(PRM_FN1_INX),d->m_posInfilter->boxFn1());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(PRM_FN2_INX),d->m_posInfilter->boxFn2());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(PRM_QX2_INX),d->m_posInfilter->boxQx2());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(PRM_FN_NCH_INX),d->m_posInfilter->boxFnNch());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(PRM_QX_NCH_INX),d->m_posInfilter->boxQxNch());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(PRM_KN_NCH_INX),d->m_posInfilter->boxKnNch());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(MAF_NUM_INX),d->m_posInfilter->boxMafNum());

  //segment pid
  d->m_mapping->insertBox2Item(d->m_pid133->boxSecondFn(),d->m_treeWidget->topLevelItem(FN_SEC_6_INX));
  d->m_mapping->insertBox2Item(d->m_pid133->boxTransTime(),d->m_treeWidget->topLevelItem(KP_SW_TIM_INX));
  d->m_mapping->insertBox2Item(d->m_pid133->boxSpdUp(),d->m_treeWidget->topLevelItem(KP_SW_SPDU_INX));
  d->m_mapping->insertBox2Item(d->m_pid133->boxSpdLow(),d->m_treeWidget->topLevelItem(KP_SW_SPDL_INX));

  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(FN_SEC_6_INX),d->m_pid133->boxSecondFn());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(KP_SW_TIM_INX),d->m_pid133->boxTransTime());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(KP_SW_SPDU_INX),d->m_pid133->boxSpdUp());
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(KP_SW_SPDL_INX),d->m_pid133->boxSpdLow());

}
void GraphPosition133::setUiVersionName()
{
  Q_D(GraphPosition133);
  d->m_versionName="V133";
  setObjectName("GraphPosition133");
}

void GraphPosition133::createPidItem()
{
  Q_D(GraphPosition133);

  QWidget *wout = new QWidget;
  QVBoxLayout *voutLayout = new QVBoxLayout(wout);
  QSpacerItem *verticalSpacer1 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  QSpacerItem *verticalSpacer2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

  QWidget *w = new QWidget;
  w->setObjectName("widget_posPid");
  QVBoxLayout *vlayout = new QVBoxLayout(w);

  d->m_pid133 = new PosPID133(w);
  connect(d->m_pid133,SIGNAL(comboBoxIndexChanged(int)),this,SLOT(onPidComboBoxKpSWIndexChanged(int)));
  vlayout->addWidget(d->m_pid133);
  w->setLayout(vlayout);

  voutLayout->addSpacerItem(verticalSpacer1);
  voutLayout->addWidget(w);
  voutLayout->addSpacerItem(verticalSpacer2);
  voutLayout->setContentsMargins(0,0,0,0);
  wout->setLayout(voutLayout);

  d->m_pEdit = d->m_pid133->boxFirstFn();
  d->m_UPID=new WidgetItem;
  d->m_UPID->setWidget(wout,true);
  d->m_scene->addItem(d->m_UPID);//take ownership

  d->m_widgetItemList.append(d->m_UPID);
}

void GraphPosition133::createItems()
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

  createPosDirItem();//add

  createArrowItems();
  createAnchorItemHelper();
  createSaturationConfigItems();

  setUpItemPosAnchors();

  adjustPosition();
  setCustumBackgroundColor();
}


void GraphPosition133::onUIFItemClicked()
{
  Q_D(GraphPosition133);
  QString title = tr("%1 axis = %2 pos filter")\
      .arg(d->m_dev->deviceConfig()->m_modeName)\
      .arg(d->m_uiWidget->uiIndexs().axisInx + 1);
  d->m_posInfilter->setWindowTitle(title);
  d->m_posInfilter->show();
  d->m_posInfilter->updatePos();

  quint16 sw = d->m_treeWidget->topLevelItem(MASK_FLAG_INX)->text(GT::COL_PAGE_TREE_VALUE).toUShort();
  d->m_posInfilter->setSW(sw);

  int index = d->m_treeWidget->topLevelItem(FIT_SEL_INX)->text(GT::COL_PAGE_TREE_VALUE).toUShort();
  d->m_posInfilter->setIIRFilterIndex(index);
}

void GraphPosition133::onFilterConfigClicked()
{
  Q_D(GraphPosition133);
  //获得mask_flag.all值
  quint16 maskFlag = d->m_posInfilter->SW();
  d->m_treeWidget->topLevelItem(MASK_FLAG_INX)->setText(GT::COL_PAGE_TREE_VALUE,QString::number(maskFlag));
  //获得fit_sel
  quint16 fitSel = d->m_posInfilter->currentIIRFilterIndex();
  d->m_treeWidget->topLevelItem(FIT_SEL_INX)->setText(GT::COL_PAGE_TREE_VALUE,QString::number(fitSel));

  foreach (QDoubleSpinBox *box, d->m_mapping->boxLists()) {
    d->m_mapping->syncBoxText2Item(box);
  }
  d->m_uiWidget->writeGenPageRAM();
}

void GraphPosition133::onFilterSaveClicked()
{
  Q_D(GraphPosition133);
  //获得mask_flag.all值
  quint16 maskFlag = d->m_posInfilter->SW();
  d->m_treeWidget->topLevelItem(MASK_FLAG_INX)->setText(GT::COL_PAGE_TREE_VALUE,QString::number(maskFlag));
  //获得fit_sel
  quint16 fitSel = d->m_posInfilter->currentIIRFilterIndex();
  d->m_treeWidget->topLevelItem(FIT_SEL_INX)->setText(GT::COL_PAGE_TREE_VALUE,QString::number(fitSel));

  foreach (QDoubleSpinBox *box, d->m_mapping->boxLists()) {
    d->m_mapping->syncBoxText2Item(box);
  }
  d->m_uiWidget->writePageFLASH();
}

void GraphPosition133::onRadioBtnClicked()
{
  Q_D(GraphPosition133);
  qint16 dir = 0;
  if(d->m_cwRBtn->isChecked())
    dir = 0;
  else
    dir = 1;

  d->m_treeWidget->topLevelItem(POSR_DIR_INX)->setText(GT::COL_PAGE_TREE_VALUE,QString::number(dir));

}

void GraphPosition133::onPidComboBoxKpSWIndexChanged(int index)
{
  Q_D(GraphPosition133);

  d->m_treeWidget->topLevelItem(KP_SW_EN_INX)->setText(GT::COL_PAGE_TREE_VALUE,QString::number(index));
}

void GraphPosition133::createPosDirItem()
{
  Q_D(GraphPosition133);
  d->m_UPOSDIR = new WidgetItem;
  QWidget *posWidget = new QWidget;
  posWidget->setObjectName("widget_posDir");
  QVBoxLayout *vlayout = new QVBoxLayout(posWidget);
  QLabel *label = new QLabel(tr("DirCtl"),posWidget);
  label->setAlignment(Qt::AlignCenter);
  label->setObjectName("label_posDirControl");
  QHBoxLayout *hlayout = new QHBoxLayout;
  d->m_cwRBtn = new QRadioButton(posWidget);
  d->m_cwRBtn->setText(tr("CW"));
  d->m_cwRBtn->setChecked(true);
  d->m_ccwRBtn = new QRadioButton(posWidget);
  d->m_ccwRBtn->setText(tr("CCW"));
  d->m_ccwRBtn->setChecked(false);
  connect(d->m_cwRBtn,SIGNAL(clicked(bool)),this,SLOT(onRadioBtnClicked()));
  connect(d->m_ccwRBtn,SIGNAL(clicked(bool)),this,SLOT(onRadioBtnClicked()));
  hlayout->addWidget(d->m_cwRBtn);
  hlayout->addWidget(d->m_ccwRBtn);
  vlayout->addWidget(label);
  vlayout->addLayout(hlayout);
  posWidget->setLayout(vlayout);
  d->m_UPOSDIR->setWidget(posWidget,true);
  d->m_scene->addItem(d->m_UPOSDIR);
  d->m_widgetItemList.append(d->m_UPOSDIR);
}
void GraphPosition133::createArrowItems()
{
  Q_D(GraphPosition133);
  d->m_A16 = new ArrowItem(d->m_Tstart->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UPOSDIR->pointF(WidgetItem::POINT_TYPE_LEFT));//比v130多出来的
  d->m_A0=new ArrowItem(d->m_UPOSDIR->pointF(WidgetItem::POINT_TYPE_RIGHT),d->m_UIF->pointF(WidgetItem::POINT_TYPE_LEFT));
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
  d->m_scene->addItem(d->m_A16);

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
  d->m_arrowList.append(d->m_A16);
}

void GraphPosition133::setUpItemPosAnchors()
{
  Q_D(GraphPosition133);
  d->m_UPID->setPos(PID_POS_X,PID_POS_Y);
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_USUM0,AnchorItemHelper::AnchorLeft,-1.5*d->m_USUM0->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_USUM0,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_USUM0,d->m_TM0,AnchorItemHelper::AnchorLeft,-0.8*d->m_USUM0->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_USUM0,d->m_TM0,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_TM0,d->m_UIF,AnchorItemHelper::AnchorLeft,-1.2*d->m_UIF->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_TM0,d->m_UIF,AnchorItemHelper::AnchorVerticalCenter);

  //add dir
  d->m_anchorHelper->addAnchor(d->m_UIF,d->m_UPOSDIR,AnchorItemHelper::AnchorLeft,-1.2*d->m_UPOSDIR->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UIF,d->m_UPOSDIR,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UPOSDIR,d->m_Tstart,AnchorItemHelper::AnchorLeft,-0.8*d->m_UPOSDIR->boundingRect().width());
  d->m_anchorHelper->addAnchor(d->m_UPOSDIR,d->m_Tstart,AnchorItemHelper::AnchorVerticalCenter);

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

  d->m_anchorHelper->addAnchor(d->m_UCCTL,d->m_Tend,AnchorItemHelper::AnchorRight,d->m_UCCTL->boundingRect().width()+50);
  d->m_anchorHelper->addAnchor(d->m_UCCTL,d->m_Tend,AnchorItemHelper::AnchorVerticalCenter);

  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_UFVB,AnchorItemHelper::AnchorHorizontalCenter);
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_UFVB,AnchorItemHelper::AnchorTop,-1.2*d->m_UFVB->boundingRect().height());

  d->m_anchorHelper->addAnchor(d->m_UFVB,d->m_UFAB,AnchorItemHelper::AnchorHorizontalCenter);
  d->m_anchorHelper->addAnchor(d->m_UFVB,d->m_UFAB,AnchorItemHelper::AnchorTop,-1.6*d->m_UFAB->boundingRect().height());

  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_UPB,AnchorItemHelper::AnchorHorizontalCenter);
  d->m_anchorHelper->addAnchor(d->m_UPID,d->m_UPB,AnchorItemHelper::AnchorBottom,1.2*d->m_UPB->boundingRect().height());

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

quint16 GraphPosition133::readNos(const QString &key)
{
  Q_D(GraphPosition133);
  bool isOk=true;
  quint16 nos=0;
  nos=d->m_dev->genCmdRead(key,d->m_uiWidget->uiIndexs().axisInx,isOk);
  return nos;
}

void GraphPosition133::syncTreeDataToUiFace()
{
  Q_D(GraphPosition133);

  //读变量，修改动态增益
  quint16 nos = readNos(MOT_NOS_KEY_NAME);
  if(nos == 0)
    nos = 1;
  double n = nos;
  double k = POW2_24/n;
  d->m_treeWidget->topLevelItem(KP_SW_SPDL_INX)->setText(GT::COL_PAGE_TREE_SCALE,QString::number(k,'f',3));
  d->m_treeWidget->topLevelItem(KP_SW_SPDU_INX)->setText(GT::COL_PAGE_TREE_SCALE,QString::number(k,'f',3));


  IGraphPosition::syncTreeDataToUiFace();

  quint16 sw_en = d->m_treeWidget->topLevelItem(KP_SW_EN_INX)->text(GT::COL_PAGE_TREE_VALUE).toUShort();
  d->m_pid133->setCurrentPidSegment(sw_en);

  qDebug()<<"sw_en = "<<sw_en;

  qint16 dir = 0;
  dir = d->m_treeWidget->topLevelItem(POSR_DIR_INX)->text(GT::COL_PAGE_TREE_VALUE).toShort();
  if(dir == 0)
    d->m_cwRBtn->setChecked(true);
  else
    d->m_ccwRBtn->setChecked(true);
}

void GraphPosition133::installDoubleSpinBoxEventFilter()
{
  Q_D(GraphPosition133);
  IGraphPosition::installDoubleSpinBoxEventFilter();

  d->m_pid133->boxSecondFn()->installEventFilter(this);
  d->m_pid133->boxTransTime()->installEventFilter(this);
  d->m_pid133->boxSpdLow()->installEventFilter(this);
  d->m_pid133->boxSpdUp()->installEventFilter(this);
}

void GraphPosition133::setDoubleSpinBoxConnections()
{
  Q_D(GraphPosition133);
  IGraphPosition::setDoubleSpinBoxConnections();
//  connect(d->m_pEdit,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_pid133->boxSecondFn(),SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_pid133->boxTransTime(),SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_pid133->boxSpdLow(),SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  connect(d->m_pid133->boxSpdUp(),SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
}

QPointF GraphPosition133::pidInitPos()
{
  return QPointF(PID_POS_X,PID_POS_Y);
}
