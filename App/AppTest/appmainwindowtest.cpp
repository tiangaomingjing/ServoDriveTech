#include "appmainwindowtest.h"
#include "ui_appmainwindowtest.h"
#include <QDebug>
#include <QTreeWidget>

#include "icom.h"
#include "qttreemanager.h"
#include "sdtglobaldef.h"
#include "gtutils.h"
#include "Kernel/globalconfig.h"
#include "Kernel/gconfigreadwriter.h"
#include "Kernel/idevreadwriter.h"
#include "Kernel/devtextrwriter.h"
#include "Kernel/deviceconfig.h"
#include "Kernel/sevdevice.h"
#include "Kernel/sevuicontroler.h"
#include "Kernel/sdassembly.h"
#include "Kernel/devcomrwriter.h"

AppMainWindowTest::AppMainWindowTest(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AppMainWindowTest),
  stop(false)
{
  ui->setupUi(this);
  initial();
}

AppMainWindowTest::~AppMainWindowTest()
{
  delete ui;
  GT::deepClearList(sdAssemblyList);
}

/**
 * @brief AppMainWindowTest::initial
 * //加载配置
 */
void AppMainWindowTest::initial()
{
  //1 根据最近配置文件，生成device ，如果初次打开使用默认设备
  //2 根据device ,生成界面
  //3 加载首选项配置信息
  mainFormInitTestCase();
}

void AppMainWindowTest::mainFormInitTestCase()
{
  QList<DeviceConfig*> devConfigList;

  GConfigReadWriter gRWriter;
  gRWriter.fillConfig(&gConfig);

  IDevReadWriter *idevRWriter=new DevTextRWriter(NULL);
  bool isOk;
  devConfigList=idevRWriter->createConfig(isOk);
  Q_ASSERT(isOk);

  for(int i=0;i<devConfigList.count();i++)
  {
    SdAssembly *sdriver=new SdAssembly();
    connect(sdriver,SIGNAL(initProgressInfo(int,QString)),this,SLOT(onProgressInfo(int,QString)));
    sdriver->init(devConfigList.at(i),&gConfig);
    qDebug()<<"new SdAssembly";
    sdAssemblyList.append(sdriver);

  }

  delete idevRWriter;
  for(int i=0;i<devConfigList.count();i++)
  {
    delete devConfigList.at(i);
  }
  devConfigList.clear();
}

//连接测试
void AppMainWindowTest::mainConnectTestCase()
{
  IDevReadWriter *idevRWriter=new DevComRWriter(NULL);
  QList<DeviceConfig*> devConfigList;
  bool isOk;
  devConfigList=idevRWriter->createConfig(isOk);

  int configCount=devConfigList.count();

  QList<SdAssembly*>sdAssemblyListTemp;
  DeviceConfig* devConfig;

  for(int i=0;i<configCount;i++)
  {
    devConfig=devConfigList.at(i);

    bool cp=false;
    for(int j=0;j<sdAssemblyList.count();j++)
    {
      currentSdAssembly=sdAssemblyList.at(j);
      if(devConfig->m_devId==0)
      {
        sdAssemblyListTemp.append(sdAssemblyList.takeAt(j));
        cp=true;
        break;
      }
    }
    if(!cp)
    {
      //根据devConfig 新建 sd
      currentSdAssembly = new SdAssembly();
      sdAssemblyListTemp.append(currentSdAssembly);
    }
  }
  //清除多余的
  for(int j=0;j<sdAssemblyList.count();j++)
  {
    currentSdAssembly=sdAssemblyList.at(j);
    delete currentSdAssembly;
  }
  sdAssemblyList.clear();

  sdAssemblyList=sdAssemblyListTemp;

}

void AppMainWindowTest::mainMemeryTestCase()
{
  for(int i=0;i<1000;i++)
  {
    GT::deepClearList(sdAssemblyList);
    GTUtils::delayms(500);
    mainFormInitTestCase();
    if(stop)
      break;
    qDebug()<<"mainMemeryTestCase"<<i;
  }
}
void AppMainWindowTest::on_pushButton_clicked()
{
  qDebug()<<"clear";
  GT::deepClearList(sdAssemblyList);
  stop=true;
}

void AppMainWindowTest::on_pushButton_init_clicked()
{
  if(sdAssemblyList.count()==0)
    mainFormInitTestCase();
  stop=false;

//  for(int i=0;i<100;i++)
//  {
//    QTreeWidget *tree=QtTreeManager::createTreeWidgetFromXmlFile("SysConfigTree.ui");
//    delete tree;
//    GTUtils::delayms(500);
//    qDebug()<<"createTreeWidgetFromXmlFile"<<i;
//  }
}


void AppMainWindowTest::on_pushButton_memery_clicked()
{
  mainMemeryTestCase();
}
void AppMainWindowTest::onProgressInfo(int v,QString msg)
{
  ui->progressBar->setValue(v);
  ui->label->setText(msg);
}
