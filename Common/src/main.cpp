#include <QCoreApplication>
#include <QDebug>

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

//程序启动时测试用例
QList<SdAssembly*>sdAssemblyList;
GlobalConfig gConfig;

void mainFormInitTestCase()
{
  QList<DeviceConfig*> devConfigList;

  GConfigReadWriter gRWriter;
  gRWriter.fillConfig(&gConfig);

  IDevReadWriter *idevRWriter=new DevTextRWriter(NULL,NULL);
  bool isOk;
  devConfigList=idevRWriter->createConfig(isOk);

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

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);


  mainFormInitTestCase();



  return a.exec();
}

