#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <QTreeWidget>

#include "qttreemanager.h"
#include "sdtglobaldef.h"
#include "Kernel/globalconfig.h"
#include "Kernel/gconfigreadwriter.h"
#include "Kernel/idevreadwriter.h"
#include "Kernel/devtextrwriter.h"
#include "Kernel/deviceconfig.h"
#include "Kernel/sevdevice.h"
#include "Kernel/sevuicontroler.h"
#include "Kernel/sdassembly.h"
#include "Kernel/devcomrwriter.h"

//程序启动时测试用例
QList<SdAssembly*>sdAssemblyList;
GlobalConfig gConfig;

SdAssembly *currentSdAssembly;

void mainFormInitTestCase()
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
    SevDevice*sev=new SevDevice(devConfigList.at(i));
    IUiControler *ui=new SevUiControler(sev,&gConfig);
    SdAssembly *sdriver=new SdAssembly(sev,ui);
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
void mainConnectTestCase()
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
      currentSdAssembly = new SdAssembly(NULL,NULL);
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

template <typename T>
class ListClear
{
public:
  ListClear(){}
  ~ListClear(){}
  static void clearList(QList<T*>&list)
  {
    T* item;
    for(int i=0;i<list.count();i++)
    {
      item=list.at(i);
      delete item;
    }
    list.clear();
  }
};

template <typename T>
static void clearListTest(QList<T*>&list)
{
  T* item;
  for(int i=0;i<list.count();i++)
  {
    item=list.at(i);
    delete item;
  }
  list.clear();
}

int main(int argc, char *argv[])
{
//  QCoreApplication a(argc, argv);
  QApplication a(argc, argv);

  mainFormInitTestCase();

  mainConnectTestCase();

  QList<QTreeWidget *>list;
  QTreeWidget *t;
  for(int i=0;i<10;i++)
  {
    t=new QTreeWidget();
    list.append(t);
  }
  qDebug()<<"before"<<list.count();
//  ListClear<QTreeWidget>::clearList(list);
  clearListTest(list);
  qDebug()<<"after"<<list.count();

  return a.exec();
}

