#include "uisrcmainwindow.h"
#include "ui_uisrcmainwindow.h"

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
#include "Kernel/iuicontroler.h"
#include "Kernel/globaluicontroler.h"

#include <QDebug>


UiSrcMainWindow::UiSrcMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::UiSrcMainWindow)
{
  ui->setupUi(this);

  QList<DeviceConfig*> devConfigList;

  GConfigReadWriter gRWriter;
  gRWriter.fillConfig(&m_gConfig);

  IDevReadWriter *idevRWriter=new DevTextRWriter(NULL);
  bool isOk;
  devConfigList=idevRWriter->createConfig(isOk);
  Q_ASSERT(isOk);

  for(int i=0;i<devConfigList.count();i++)
  {
    SdAssembly *sdriver=new SdAssembly();
    connect(sdriver,SIGNAL(initProgressInfo(int,QString)),this,SLOT(onProgressInfo(int,QString)));
    sdriver->init(devConfigList.at(i),&m_gConfig);
    qDebug()<<"new SdAssembly";
    m_sdAssemblyList.append(sdriver);
  }

  delete idevRWriter;
  for(int i=0;i<devConfigList.count();i++)
  {
    delete devConfigList.at(i);
  }
  devConfigList.clear();
}

UiSrcMainWindow::~UiSrcMainWindow()
{
  delete ui;
}
