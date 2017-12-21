#include "appmainwindowtest.h"
#include "ui_appmainwindowtest.h"
#include <QDebug>
#include <QTreeWidget>
#include <QFileInfo>
#include <QFileDialog>
#include <QtQml>

#include "icom.h"
#include "qttreemanager.h"
#include "sdtglobaldef.h"
#include "gtutils.h"
#include "Kernel/globalconfig.h"
#include "Kernel/gconfigreadwriter.h"
#include "Kernel/idevreadwriter.h"
#include "Kernel/devtextrwriter.h"
#include "Kernel/deviceconfig.h"
#include "Kernel/sevuicontroler.h"
#include "Kernel/sdassembly.h"
#include "Kernel/devcomrwriter.h"

#include "changframaddr.h"
#include "sevdevice.h"

AppMainWindowTest::AppMainWindowTest(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AppMainWindowTest),
  stop(false),
  m_filePath(".")
{
  ui->setupUi(this);
  qmlRegisterType<SevDevice>("QtCppClass", 1, 0, "SevDevice");
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
void AppMainWindowTest::processBarInfo(void *bar,short *v)
{
  int value=*v;
  QProgressBar *pBar=static_cast<QProgressBar *>(bar);
  pBar->setValue(value);
}

void AppMainWindowTest::mainFormInitTestCase()
{
  QList<DeviceConfig*> devConfigList;

  GConfigReadWriter gRWriter;
  gRWriter.fillConfig(&gConfig);

  IDevReadWriter *idevRWriter=new DevTextRWriter(NULL);
  bool isOk;
  devConfigList=idevRWriter->createConfig(processBarInfo,(void*)ui->progressBar,isOk);
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
  devConfigList=idevRWriter->createConfig(processBarInfo,(void*)ui->progressBar,isOk);
  Q_ASSERT(isOk);

  int configCount=devConfigList.count();
  qDebug()<<"devConfigList.count()"<<configCount;

  QList<SdAssembly*>sdAssemblyListTemp;
  DeviceConfig* devConfig;

  for(int i=0;i<configCount;i++)
  {
    devConfig=devConfigList.at(i);

    bool cp=false;
    for(int j=0;j<sdAssemblyList.count();j++)
    {

      currentSdAssembly=sdAssemblyList.at(j);
      DeviceConfig* tc=currentSdAssembly->sevDevice()->deviceConfig();
      bool isEqual=devConfig->isEqual(*tc);
      qDebug()<<"isEqual"<<isEqual;
//      Q_ASSERT(isEqual);
      if(isEqual)//与原有的匹配
      {
        qDebug()<<"sdAssemblyListTemp.append(sdAssemblyList.takeAt(j))";
        sdAssemblyListTemp.append(sdAssemblyList.takeAt(j));
        cp=true;
        break;
      }
    }
    if(!cp)
    {
      //根据devConfig 新建 sd
      qDebug()<<"new SdAssembly()";
      currentSdAssembly = new SdAssembly();
      currentSdAssembly->init(devConfig,&gConfig);
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
  qDebug()<<msg;
}

void AppMainWindowTest::on_actionChangeAddr_triggered()
{
  QString filename;
  filename = QFileDialog::getOpenFileName(this, tr("Open XML File"), m_filePath, tr("XML Files(*.xml)"));
  if (filename.isNull())
  {
    //QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    return;
  }
  QFileInfo fileInfo;
  fileInfo.setFile(filename);
  m_filePath=fileInfo.filePath()+"/";
  ChangFramAddr::changeTreeAddr(filename,32768);
  qDebug()<<"save file";
}

void AppMainWindowTest::on_pushButton_connectTest_clicked()
{
  qDebug()<<"connect test clicked";
  mainConnectTestCase();
}
