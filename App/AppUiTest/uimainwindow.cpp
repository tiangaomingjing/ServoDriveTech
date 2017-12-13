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
#include "Kernel/globaluicontroler.h"


class UiMainWindowPrivate{
  Q_DECLARE_PUBLIC(UiMainWindow)
public:
  UiMainWindowPrivate();
  ~UiMainWindowPrivate();

  QList<SdAssembly*>m_sdAssemblyList;
  IUiControler *m_gUiControl;
  GlobalConfig m_gConfig;
  SdAssembly *m_currentSdAssembly;

  QAction *actTestNew;
  QAction *actTestAddTree;
  QAction *actTest;
  QAction *actTest2;
  QAction *actReadFlash;

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

  staticUiInit();

}

UiMainWindow::~UiMainWindow()
{
  delete ui;
}
bool UiMainWindow::init()
{
  Q_D(UiMainWindow);
  readConfig();
  deviceInit();
  navigationTreeInit();
  globalUiPageInit();

  int i=0;
  while (ui->stackedWidget->count()) {
    delete ui->stackedWidget->widget(0);
    qDebug()<<"delete stackedWidget "<<i;
    i++;
  }
  IUiControler *uiCtr;
  QWidget *w;
  SdAssembly * sd;
  int uiCount;
  for(int i=0;i<d->m_sdAssemblyList.count();i++)
  {
    sd=d->m_sdAssemblyList.at(i);
    uiCtr=sd->uiControler();
    uiCount=uiCtr->uiCount();
    qDebug()<<"uiCount"<<uiCount;
    for(int i=0;i<uiCount;i++)
    {
      w=static_cast<QWidget *>(uiCtr->uiAt(i));
      ui->stackedWidget->addWidget(w);
    }
  }

  uiCtr=d->m_gUiControl;
  uiCount=uiCtr->uiCount();
  qDebug()<<"uiCount"<<uiCount;
  for(int i=0;i<uiCount;i++)
  {
    w=static_cast<QWidget *>(uiCtr->uiAt(i));
    ui->stackedWidget->addWidget(w);
  }

  return true;
}

void UiMainWindow::readConfig()
{
  Q_D(UiMainWindow);

  GConfigReadWriter gRWriter;
  gRWriter.fillConfig(&d->m_gConfig);
}

bool UiMainWindow::deviceInit()
{
  Q_D(UiMainWindow);
  QList<DeviceConfig*> devConfigList;

  IDevReadWriter *idevRWriter=new DevTextRWriter(NULL);
  bool isOk;
  devConfigList=idevRWriter->createConfig(isOk);
  Q_ASSERT(isOk);

  for(int i=0;i<devConfigList.count();i++)
  {
    qDebug()<<"************************new SdAssembly "<<i;
    SdAssembly *sdriver=new SdAssembly();
    connect(sdriver,SIGNAL(initProgressInfo(int,QString)),this,SLOT(onProgressInfo(int,QString)));
    sdriver->init(devConfigList.at(i),&d->m_gConfig);
    d->m_sdAssemblyList.append(sdriver);
  }

  delete idevRWriter;
  GT::deepClearList(devConfigList);
  return true;
}

void UiMainWindow::navigationTreeInit()
{
  Q_D(UiMainWindow);

  NavShowType type;
  type=getNavShowType();
  switch (type)
  {
  case NAV_SHOW_SINGLE:
  {
  }
    break;
  case NAV_SHOW_SINGLE_1_4_6://单个4.6轴设备
  {
    qDebug()<<"build nav show singal 4_6";
    d->m_currentSdAssembly=d->m_sdAssemblyList.at(0);
    QTreeWidgetItem *axisItem=NULL;
    QTreeWidgetItem *globalItem=NULL;
    QTreeWidgetItem *plotItem=NULL;
    int axisNum=d->m_currentSdAssembly->sevDevice()->axisNum();
    int pageIndex=0;
    int pageNum=0;
    for(int i=0;i<axisNum;i++)
    {
      axisItem=d->m_currentSdAssembly->sevDevice()->targetTree()->child(0)->clone();
      axisItem->setText(0,tr("Axis_%1").arg(i+1));
      ui->treeWidget->addTopLevelItem(axisItem);
      for(int j=0;j<axisItem->childCount();j++)
      {
        axisItem->child(j)->setText(1,QString::number(i));
        axisItem->child(j)->setText(4,QString::number(pageIndex));
        pageIndex++;
      }
    }
    pageNum=axisItem->childCount();

    globalItem=d->m_currentSdAssembly->sevDevice()->targetTree()->child(1);
    int globalCount=globalItem->childCount();
    QTreeWidgetItem *item=NULL;
    for(int i=0;i<globalCount;i++)
    {
      item=globalItem->child(i)->clone();
      item->setText(4,QString::number(pageIndex));
      ui->treeWidget->addTopLevelItem(item);
      pageIndex++;
    }
    qDebug()<<"globalCount"<<globalCount;

    qDebug()<<"axisNum*pageNum+globalCount"<<axisNum*pageNum+globalCount;
    plotItem=new QTreeWidgetItem;
    plotItem->setText(0,tr("Plot"));
    plotItem->setText(4,QString::number(pageIndex));
    ui->treeWidget->addTopLevelItem(plotItem);

    ui->treeWidget->setColumnCount(6);
    ui->treeWidget->expandItem(ui->treeWidget->topLevelItem(0));
  }
    break;
  case NAV_SHOW_MIX:
  {
    qDebug()<<"build nav show mix";
    QTreeWidgetItem *deviceItem;
    QTreeWidgetItem *plotItem;
    QTreeWidgetItem *axisItem;
    QTreeWidgetItem *globalItem=NULL;
    SdAssembly * sd;
    int pageIndex=0;
    for(int  i=0;i<d->m_sdAssemblyList.count();i++)
    {
      sd=d->m_sdAssemblyList.at(i);
      deviceItem=new QTreeWidgetItem;
      deviceItem->setText(0,sd->sevDevice()->modelName());
      qDebug()<<"deviceItem->setText";

      int axisNum=sd->sevDevice()->axisNum();
      int pageNum=0;
      for(int i=0;i<axisNum;i++)
      {
        axisItem=sd->sevDevice()->targetTree()->child(0)->clone();
        axisItem->setText(0,tr("Axis_%1").arg(i+1));
        for(int j=0;j<axisItem->childCount();j++)
        {
          axisItem->child(j)->setText(1,QString::number(i));
          axisItem->child(j)->setText(4,QString::number(pageIndex));
          pageIndex++;
        }
        deviceItem->addChild(axisItem);
      }
      pageNum=axisItem->childCount();

      globalItem=sd->sevDevice()->targetTree()->child(1);
      int globalCount=globalItem->childCount();
      QTreeWidgetItem *item=NULL;
      for(int i=0;i<globalCount;i++)
      {
        item=globalItem->child(i)->clone();
        item->setText(4,QString::number(pageIndex));
        deviceItem->addChild(item);
        pageIndex++;
      }

      ui->treeWidget->addTopLevelItem(deviceItem);
    }
    plotItem=new QTreeWidgetItem;
    plotItem->setText(0,tr("Plot"));
    plotItem->setText(4,QString::number(pageIndex));
    ui->treeWidget->addTopLevelItem(plotItem);

    ui->treeWidget->setColumnCount(6);
    ui->treeWidget->expandItem(ui->treeWidget->topLevelItem(0)->child(0));

  }
    break;
  default:
    break;
  }
}

void UiMainWindow::globalUiPageInit()
{
  Q_D(UiMainWindow);

  d->m_gUiControl=new GlobalUiControler(&d->m_gConfig);
  d->m_gUiControl->createUis();
}

void UiMainWindow::clearDevice()
{
  Q_D(UiMainWindow);

  qDebug()<<"clear device";
  GT::deepClearList(d->m_sdAssemblyList);
}

void UiMainWindow::clearNavigationTree()
{
  qDebug()<<"clear navigation tree";
  ui->treeWidget->clear();
}
void UiMainWindow::clearGlobalUiPage()
{
  Q_D(UiMainWindow);

  qDebug()<<"clear global ui page";
  delete d->m_gUiControl;
}

void UiMainWindow::clear()
{
  clearDevice();
  clearNavigationTree();
  clearGlobalUiPage();
}

void UiMainWindow::staticUiInit()
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

  d->actReadFlash =new QAction(tr("ReadFLASH"),this);
  ui->mainToolBar->addAction(d->actReadFlash);
  connect(d->actReadFlash,SIGNAL(triggered(bool)),this,SLOT(onActReadFlashTestClicked()));

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
  qDebug()<<"act new test clicked";
  clear();
  qDebug()<<"stackedWidget count "<<ui->stackedWidget->count();
  init();
}

void UiMainWindow::onActAddTreeTestClicked()
{
  qDebug()<<"act add tree test clicked";

  QString file=GTUtils::sysPath()+"/SD6x/SD61/V129/RamPrm_AllAxis.xml";
  QTreeWidget *tree=QtTreeManager::createTreeWidgetFromXmlFile(file);
  ui->stackedWidget->addWidget(tree);
}
void UiMainWindow::onActReadFlashTestClicked()
{
  QWidget *cw=ui->stackedWidget->currentWidget();
  IUiWidget *ui=dynamic_cast<IUiWidget *>(cw);//向下转型时使用dynamic_cast
  qDebug()<<ui->objectName();
  ui->readFLASH();
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
  Q_D(UiMainWindow);

  UiMainWindow::NavShowType type;

  int deviceCount=d->m_sdAssemblyList.count();
  if(deviceCount>1)
  {
    type=UiMainWindow::NAV_SHOW_SINGLE;
    for(int i=0;i<deviceCount;i++)
    {
      if(d->m_sdAssemblyList.at(i)->sevDevice()->axisNum()!=1)
      {
        type=UiMainWindow::NAV_SHOW_MIX;
        break;
      }
    }
  }
  else
    type=UiMainWindow::NAV_SHOW_SINGLE_1_4_6;

//type=UiMainWindow::NAV_SHOW_SINGLE_1_4_6;
  qDebug()<<"Navigation type="<<type;
  return type;
}
