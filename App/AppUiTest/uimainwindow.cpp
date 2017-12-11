#include "uimainwindow.h"
#include "ui_uimainwindow.h"

#include <QDebug>

#include "icom.h"
#include "qttreemanager.h"
#include "sdtglobaldef.h"
#include "gtutils.h"
#include "IUiWidget/iuiwidget.h"

#include "Kernel/globalconfig.h"
#include "Kernel/gconfigreadwriter.h"
#include "Kernel/idevreadwriter.h"
#include "Kernel/devtextrwriter.h"
#include "Kernel/deviceconfig.h"
#include "Kernel/sevdevice.h"
#include "Kernel/sevuicontroler.h"
#include "Kernel/sdassembly.h"
#include "Kernel/devcomrwriter.h"
#include "Kernel/iuicontroler.h"


class UiMainWindowPrivate{
  Q_DECLARE_PUBLIC(UiMainWindow)
public:
  UiMainWindowPrivate();
  ~UiMainWindowPrivate();

  QList<SdAssembly*>m_sdAssemblyList;
  GlobalConfig m_gConfig;
  SdAssembly *m_currentSdAssembly;

  QAction *actTestNew;
  QAction *actTestAddTree;
  QAction *actTest;
  QAction *actTest2;
  QAction *actTest3[100];

  UiMainWindow *q_ptr;
};

UiMainWindowPrivate::UiMainWindowPrivate()
{

}

UiMainWindowPrivate::~UiMainWindowPrivate()
{

}

UiMainWindow::UiMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::UiMainWindow),
  d_ptr(new UiMainWindowPrivate)
{
  ui->setupUi(this);
  d_ptr->q_ptr=this;

  initStaticUi();
}

UiMainWindow::~UiMainWindow()
{
  delete ui;
}
bool UiMainWindow::init()
{
  Q_D(UiMainWindow);
  servoInit();
  navigationInit();

  int i=0;
  while (ui->stackedWidget->count()) {
    delete ui->stackedWidget->widget(0);
    qDebug()<<"delete stackedWidget "<<i;
    i++;
  }
  IUiControler *uiCtr;
  QWidget *w;
  uiCtr=d->m_currentSdAssembly->uiControler();
  int uiCount=uiCtr->uiCount();
  qDebug()<<"uiCount"<<uiCount;
  for(int i=0;i<uiCount;i++)
  {
    w=static_cast<QWidget *>(uiCtr->uiAt(i));
    ui->stackedWidget->addWidget(w);
  }
  return true;
}

bool UiMainWindow::servoInit()
{
  Q_D(UiMainWindow);
  QList<DeviceConfig*> devConfigList;

  GConfigReadWriter gRWriter;
  gRWriter.fillConfig(&d->m_gConfig);

  IDevReadWriter *idevRWriter=new DevTextRWriter(NULL);
  bool isOk;
  devConfigList=idevRWriter->createConfig(isOk);
  Q_ASSERT(isOk);

  for(int i=0;i<devConfigList.count();i++)
  {
    SdAssembly *sdriver=new SdAssembly();
    connect(sdriver,SIGNAL(initProgressInfo(int,QString)),this,SLOT(onProgressInfo(int,QString)));
    sdriver->init(devConfigList.at(i),&d->m_gConfig);
    qDebug()<<"new SdAssembly";
    d->m_sdAssemblyList.append(sdriver);

  }

  delete idevRWriter;
  for(int i=0;i<devConfigList.count();i++)
  {
    delete devConfigList.at(i);
  }
  devConfigList.clear();
  return true;
}

void UiMainWindow::navigationInit()
{
  Q_D(UiMainWindow);
//  for(int i=0;i<ui->treeWidget->topLevelItemCount();i++)
//    delete ui->treeWidget->topLevelItem(i);
  ui->treeWidget->clear();

  NavShowType type;
  type=getNavShowType();
  switch (type)
  {
  case NAV_SHOW_SIGNAL:

    break;
  case NAV_SHOW_SIGNAL_4_6://单个4.6轴设备
  {
    d->m_currentSdAssembly=d->m_sdAssemblyList.at(0);
    QTreeWidgetItem *axisItem=NULL;
    QTreeWidgetItem *globalItem=NULL;
    QTreeWidgetItem *plotItem=NULL;
    int axisNum=d->m_currentSdAssembly->sevDevice()->axisNum();
    int pageNum=0;
    for(int i=0;i<axisNum;i++)
    {
      axisItem=d->m_currentSdAssembly->sevDevice()->targetTree()->child(0)->clone();
      axisItem->setText(0,tr("Axis_%1").arg(i+1));
      ui->treeWidget->addTopLevelItem(axisItem);
      for(int j=0;j<axisItem->childCount();j++)
      {
        axisItem->child(j)->setText(1,QString::number(i));
        axisItem->child(j)->setText(4,QString::number(j+axisItem->childCount()*i));
      }
    }
    pageNum=axisItem->childCount();

    globalItem=d->m_currentSdAssembly->sevDevice()->targetTree()->child(1);
    int globalCount=globalItem->childCount();
    QTreeWidgetItem *item=NULL;
    for(int i=0;i<globalCount;i++)
    {
      item=globalItem->child(i)->clone();
      item->setText(4,QString::number(i+axisNum*pageNum));
      ui->treeWidget->addTopLevelItem(item);
    }
    qDebug()<<"globalCount"<<globalCount;

    qDebug()<<"axisNum*pageNum+globalCount"<<axisNum*pageNum+globalCount;
    plotItem=d->m_currentSdAssembly->sevDevice()->targetTree()->child(2)->clone();
    plotItem->setText(4,QString::number(axisNum*pageNum+globalCount));
    ui->treeWidget->addTopLevelItem(plotItem);

    ui->treeWidget->setColumnCount(6);
    ui->treeWidget->expandItem(ui->treeWidget->topLevelItem(0));
  }
    break;
  case NAV_SHOW_MIX:

    break;
  default:
    break;
  }
}

void UiMainWindow::initStaticUi()
{
  Q_D(UiMainWindow);

  d->actTest=new QAction(tr("test"),this);
  ui->mainToolBar->addAction(d->actTest);
  connect(d->actTest,SIGNAL(triggered(bool)),this,SLOT(onActTestClicked()));

  d->actTest2=new QAction(tr("test2"),this);
  ui->mainToolBar->addAction(d->actTest2);
  connect(d->actTest2,SIGNAL(triggered(bool)),this,SLOT(onActTest2Clicked()));

  d->actTestNew=new QAction(tr("testNew"),this);
  ui->mainToolBar->addAction(d->actTestNew);
  connect(d->actTestNew,SIGNAL(triggered(bool)),this,SLOT(onActNewTestClicked()));

  d->actTestAddTree =new QAction(tr("testAddTree"),this);
  ui->mainToolBar->addAction(d->actTestAddTree);
  connect(d->actTestAddTree,SIGNAL(triggered(bool)),this,SLOT(onActAddTreeTestClicked()));

  connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(onNavTreeWidgetItemClicked(QTreeWidgetItem*,int)));
}

void UiMainWindow::onProgressInfo(int v, QString msg)
{
  ui->progressBar->setValue(v);
  qDebug()<<"progress infomation "<<msg;
}
void UiMainWindow::onActTestClicked()
{
  qDebug()<<"act test clicked";
}
void UiMainWindow::onActTest2Clicked()
{
  qDebug()<<"act test2 clicked";
}
void UiMainWindow::onActNewTestClicked()
{
  Q_D(UiMainWindow);

  qDebug()<<"act new test clicked";
  GT::deepClearList(d->m_sdAssemblyList);
  GTUtils::delayms(500);
  init();
}

void UiMainWindow::onActAddTreeTestClicked()
{
  qDebug()<<"act add tree test clicked";

  QString file=GTUtils::sysPath()+"/SD6x/SD61/V129/RamPrm_AllAxis.xml";
  QTreeWidget *tree=QtTreeManager::createTreeWidgetFromXmlFile(file);
  ui->stackedWidget->addWidget(tree);
}

void UiMainWindow::onNavTreeWidgetItemClicked(QTreeWidgetItem *item, int column)
{
  Q_UNUSED(column);
  if(item->childCount()==0)
  {
    int index=item->text(4).toInt();
    if(index<ui->stackedWidget->count())
      ui->stackedWidget->setCurrentIndex(index);
    qDebug()<<"index"<<index <<"ui->stackedWidget->count()"<<ui->stackedWidget->count();
  }
}

//----private--------
UiMainWindow::NavShowType UiMainWindow::getNavShowType()
{
  //根据m_sdAssemblyList信息，决定type
  UiMainWindow::NavShowType type=UiMainWindow::NAV_SHOW_SIGNAL_4_6;
  return type;
}
