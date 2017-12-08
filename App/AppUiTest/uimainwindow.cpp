#include "uimainwindow.h"
#include "ui_uimainwindow.h"

#include <QDebug>

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


UiMainWindow::UiMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::UiMainWindow)
{
  ui->setupUi(this);

}

UiMainWindow::~UiMainWindow()
{
  delete ui;
}
bool UiMainWindow::init()
{
  servoInit();
  navigationInit();
  return true;
}

bool UiMainWindow::servoInit()
{
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
  return true;
}

void UiMainWindow::navigationInit()
{
  ui->treeWidget->clear();
  NavShowType type;
  type=NAV_SHOW_SIGNAL;
  switch (type) {
  case NAV_SHOW_SIGNAL:

    break;
  case NAV_SHOW_MIX:

    break;
  default:
    break;
  }
}

void UiMainWindow::onProgressInfo(int v, QString msg)
{
  ui->progressBar->setValue(v);
}
