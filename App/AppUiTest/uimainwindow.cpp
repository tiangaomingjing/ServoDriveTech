#include "uimainwindow.h"
#include "ui_uimainwindow.h"

#include <QDebug>
#include <QtQml>
#include <QTranslator>

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
#include "Kernel/sevuicontroler.h"
#include "Kernel/sdassembly.h"
#include "Kernel/devcomrwriter.h"
#include "Kernel/iuicontroler.h"
#include "Kernel/globaluicontroler.h"
#include "sevdevice.h"


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
  QAction *actTestWriteFlash;
  QAction *actTest;
  QAction *actTest2;
  QAction *actReadFlash;
  QAction *actQuery;

  QAction *actNewBySelect;
  QAction *actConnect;
  QAction *actDisConnect;

  QAction *actLangChinese;
  QAction *actLangEnglish;

  QTranslator m_langTrans;

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
  clearStackedWidget();
  d_ptr->q_ptr=this;

  qmlRegisterType<SevDevice>("QtCppClass", 1, 0, "SevDevice");
  staticUiInit();

}

UiMainWindow::~UiMainWindow()
{
  delete ui;
}
void UiMainWindow::clearStackedWidget()
{
  int i=0;
  while (ui->stackedWidget->count()) {
    delete ui->stackedWidget->widget(0);
    qDebug()<<"delete stackedWidget "<<i;
    i++;
  }
}

void UiMainWindow::stackedWidgetInit()
{
  Q_D(UiMainWindow);

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
}
void UiMainWindow::removeAllStackedWidget()
{
  int i=0;
  while (ui->stackedWidget->count()) {
    ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    qDebug()<<"remove stackedWidget "<<i;
    i++;
  }
}

bool UiMainWindow::init()
{
  readConfig();
  deviceInit();
  navigationTreeInit();
  globalUiPageInit();
  stackedWidgetInit();

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
  devConfigList=idevRWriter->createConfig(processCallBack,(void*)ui->progressBar,isOk);
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
  clearStackedWidget();
}

void UiMainWindow::staticUiInit()
{
  Q_D(UiMainWindow);

  d->actTest=new QAction(tr("testConnet"),this);
  ui->mainToolBar->addAction(d->actTest);
  connect(d->actTest,SIGNAL(triggered(bool)),this,SLOT(onActConnectTestClicked()));

  d->actTest2=new QAction(tr("testDisConnect"),this);
  ui->mainToolBar->addAction(d->actTest2);
  connect(d->actTest2,SIGNAL(triggered(bool)),this,SLOT(onActDisConnectTestClicked()));

  d->actTestNew=new QAction(tr("testNew"),this);
  ui->mainToolBar->addAction(d->actTestNew);
  connect(d->actTestNew,SIGNAL(triggered(bool)),this,SLOT(onActNewTestClicked()));

  d->actTestWriteFlash =new QAction(tr("testWriteFlash"),this);
  ui->mainToolBar->addAction(d->actTestWriteFlash);
  connect(d->actTestWriteFlash,SIGNAL(triggered(bool)),this,SLOT(onActWriteFLASHTestClicked()));

  d->actReadFlash =new QAction(tr("ReadFLASH"),this);
  ui->mainToolBar->addAction(d->actReadFlash);
  connect(d->actReadFlash,SIGNAL(triggered(bool)),this,SLOT(onActReadFlashTestClicked()));

  connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(onNavTreeWidgetItemClicked(QTreeWidgetItem*,int)));

  d->actQuery =new QAction(tr("queryConnect"),this);
  ui->mainToolBar->addAction(d->actQuery);
  connect(d->actQuery,SIGNAL(triggered(bool)),this,SLOT(onActQueryTestClicked()));

  ui->mainToolBar->addSeparator();

  d->actConnect =new QAction(tr("connect"),this);
  d->actConnect->setCheckable(true);
  d->actConnect->setChecked(false);
  d->actConnect->setIcon(QIcon(GTUtils::iconPath()+"menu_connect.png"));
  ui->mainToolBar->addAction(d->actConnect);
  connect(d->actConnect,SIGNAL(triggered(bool)),this,SLOT(onActConnectClicked()));

  d->actDisConnect =new QAction(tr("disnet"),this);
  d->actDisConnect->setCheckable(true);
  d->actDisConnect->setChecked(true);
  d->actDisConnect->setIcon(QIcon(GTUtils::iconPath()+"menu_disconnect.png"));
  ui->mainToolBar->addAction(d->actDisConnect);
  connect(d->actDisConnect,SIGNAL(triggered(bool)),this,SLOT(onActDisConnectClicked()));

  QActionGroup *aGroup=new QActionGroup(this);
  aGroup->addAction(d->actConnect);
  aGroup->addAction(d->actDisConnect);

  ui->mainToolBar->addSeparator();

  d->actNewBySelect =new QAction(tr("SelectNew"),this);
  d->actNewBySelect->setIcon(QIcon(GTUtils::iconPath()+"menu_new.png"));
  ui->mainToolBar->addAction(d->actNewBySelect);
  connect(d->actNewBySelect,SIGNAL(triggered(bool)),this,SLOT(onActNewSelectClicked()));

  ui->mainToolBar->addSeparator();
  d->actLangChinese =new QAction(tr("chinese"),this);
//  d->actLangChinese->setIcon(QIcon(GTUtils::iconPath()+"menu_new.png"));
  ui->mainToolBar->addAction(d->actLangChinese);
  connect(d->actLangChinese,SIGNAL(triggered(bool)),this,SLOT(onActChineseClicked()));

  d->actLangEnglish =new QAction(tr("english"),this);
//  d->actLangChinese->setIcon(QIcon(GTUtils::iconPath()+"menu_new.png"));
  ui->mainToolBar->addAction(d->actLangEnglish);
  connect(d->actLangEnglish,SIGNAL(triggered(bool)),this,SLOT(onActEnglishClicked()));


}

void UiMainWindow::onProgressInfo(int v, QString msg)
{
  ui->progressBar->setValue(v);
  qDebug()<<"progress infomation "<<msg;
}
void UiMainWindow::processCallBack(void *argv,short *value)
{
  qDebug()<<"progress value ="<<*value;
  QProgressBar *bar=static_cast<QProgressBar *>(argv);
  bar->setValue(*value);
  qApp->processEvents();
}

void UiMainWindow::onActConnectTestClicked()
{
  Q_D(UiMainWindow);
  qDebug()<<"act connect test clicked";
  bool isConnect=true;
  foreach (SdAssembly *sd, d->m_sdAssemblyList)
  {
    isConnect=sd->sevDevice()->enableConnection(processCallBack,(void *)ui->progressBar);
    if(isConnect==false)
    {
      ui->progressBar->setValue(0);
      qDebug()<<"connect false";
      break;
    }
    qDebug()<<isConnect;
  }
}
void UiMainWindow::onActDisConnectTestClicked()
{
  Q_D(UiMainWindow);
  qDebug()<<"act disconnect test clicked";
  foreach (SdAssembly *sd, d->m_sdAssemblyList)
  {
    sd->sevDevice()->disableConnection();
  }
  ui->progressBar->setValue(0);
}
void UiMainWindow::onActNewTestClicked()
{
  qDebug()<<"act new test clicked";
  clear();
  qDebug()<<"stackedWidget count "<<ui->stackedWidget->count();
  init();
}

void UiMainWindow::onActWriteFLASHTestClicked()
{
  qDebug()<<"act add write flash test clicked";
  QWidget *cw=ui->stackedWidget->currentWidget();
  IUiWidget *ui=dynamic_cast<IUiWidget *>(cw);//向下转型时使用dynamic_cast
  qDebug()<<ui->objectName();
  ui->writePageFLASH();

}
void UiMainWindow::onActReadFlashTestClicked()
{
  QWidget *cw=ui->stackedWidget->currentWidget();
  IUiWidget *ui=dynamic_cast<IUiWidget *>(cw);//向下转型时使用dynamic_cast
  qDebug()<<ui->objectName();
  ui->readPageFLASH();
}
void UiMainWindow::onActQueryTestClicked()
{
  qDebug()<<"query connect clicked";
}
void UiMainWindow::onActConnectClicked()
{
  qDebug()<<"connect clicked";
}

void UiMainWindow::onActDisConnectClicked()
{
  qDebug()<<"dis connect clicked";
}

void UiMainWindow::onActNewSelectClicked()
{
  Q_D(UiMainWindow);

  QList<DeviceConfig *>configList;//just for test
  qDebug()<<"new select  clicked";
  //if 确定修改按下
  DeviceConfig *config=new DeviceConfig;
  //SD42 V129 test
  config->m_pwrId= 21000509;
  config->m_ctrId= 0;
  config->m_version="V129";
  config->m_comType=1;
  config->m_axisNum=4;
  config->m_devId=0;
  config->m_fpgaId=0;
  config->m_typeName="SD4x";
  config->m_modeName="SD42";
  config->m_rnStationId=0xf0;
  configList.append(config);


  //SD61 V129 test
  config=new DeviceConfig;
  config->m_pwrId= 21000541;
  config->m_ctrId= 0;
  config->m_version="V129";
  config->m_comType=1;
  config->m_axisNum=6;
  config->m_devId=0;
  config->m_fpgaId=0;
  config->m_typeName="SD6x";
  config->m_modeName="SD61";
  config->m_rnStationId=0xf1;
  configList.append(config);

  int configCount=configList.count();
  qDebug()<<"configList.count()"<<configCount;

  QList<SdAssembly*>sdAssemblyListTemp;
  DeviceConfig* devConfig;
  SdAssembly* currentSdAssembly;

  for(int i=0;i<configCount;i++)
  {
    devConfig=configList.at(i);
    qDebug()<<"devconfig:"<<tr("pwrid=%1,ctrid=%2,comtype=%3,version=%4,stationid=%5").arg(devConfig->m_pwrId)\
              .arg(devConfig->m_ctrId).arg(devConfig->m_comType).arg(devConfig->m_version).arg(devConfig->m_rnStationId);

    bool cp=false;
    for(int j=0;j<d->m_sdAssemblyList.count();j++)
    {

      currentSdAssembly=d->m_sdAssemblyList.at(j);
      DeviceConfig* tc=currentSdAssembly->sevDevice()->deviceConfig();
      bool isEqual=devConfig->isEqual(*tc);
      qDebug()<<"isEqual"<<isEqual;
//      Q_ASSERT(isEqual);
      if(isEqual)//与原有的匹配
      {
        qDebug()<<"sdAssemblyListTemp.append(sdAssemblyList.takeAt(j))";
        sdAssemblyListTemp.append(d->m_sdAssemblyList.takeAt(j));
        cp=true;
        break;
      }
    }
    if(!cp)
    {
      //根据devConfig 新建 sd
      qDebug()<<"new SdAssembly()";
      currentSdAssembly = new SdAssembly();
      connect(currentSdAssembly,SIGNAL(initProgressInfo(int,QString)),this,SLOT(onProgressInfo(int,QString)));
      currentSdAssembly->init(devConfig,&d->m_gConfig);
      sdAssemblyListTemp.append(currentSdAssembly);
    }
  }
//  //清除多余的
//  for(int j=0;j<d->m_sdAssemblyList.count();j++)
//  {
//    currentSdAssembly=d->m_sdAssemblyList.at(j);
//    delete currentSdAssembly;
//  }
//  d->m_sdAssemblyList.clear();
  GT::deepClearList(d->m_sdAssemblyList);


  d->m_sdAssemblyList=sdAssemblyListTemp;
  qDebug()<<"after sdAssembly list count"<<d->m_sdAssemblyList.count();

  //这里还有内存泄漏
//  removeAllStackedWidget();
//  clearNavigationTree();
//  clearGlobalUiPage();

//  navigationTreeInit();
//  globalUiPageInit();
//  stackedWidgetInit();

  GT::deepClearList(configList);
}

void UiMainWindow::onActChineseClicked()
{
  //测试没有通过
  Q_D(UiMainWindow);
  QString langPath= GTUtils::languagePath();
  qDebug()<<"chinese"<<langPath;
  d->m_langTrans.load("ch_main.qm",langPath);
  qApp->installTranslator(&d->m_langTrans);
  ui->retranslateUi(this);
  //这个只能使用Ui工具生成的界面
  //如果自己用代码生成的还要重新定义retranslate方法
  //所以目前采用改变配置文件，main()里加载，重启生效
}

void UiMainWindow::onActEnglishClicked()
{
  //测试没有通过
  Q_D(UiMainWindow);
  QString langPath= GTUtils::languagePath();
  qDebug()<<"english"<<langPath;
  d->m_langTrans.load("en_main.qm",langPath);
  qApp->installTranslator(&d->m_langTrans);
  ui->retranslateUi(this);
  //这个只能使用Ui工具生成的界面
  //如果自己用代码生成的还要重新定义retranslate方法
  //所以目前采用改变配置文件，main()里加载，重启生效
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
