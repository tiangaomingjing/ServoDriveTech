#include "sdassembly.h"
#include "sevdevice.h"
#include <QDebug>
#include "iuicontroler.h"
#include "sevdevice.h"
#include "iuicontroler.h"
#include "sevuicontroler.h"

SdAssembly::SdAssembly(QObject *parent):QObject(parent)
{

}

SdAssembly::~SdAssembly()
{
  qDebug()<<"SdAssembly-->destruct";
}
bool SdAssembly::init(const DeviceConfig *dConfig,GlobalConfig *gConfig)
{
  emit initProgressInfo(10,tr("SdAssembly init"));
  m_device=new SevDevice(this);
  connect(m_device,SIGNAL(initProgressInfo(int,QString)),this,SIGNAL(initProgressInfo(int,QString)));
  m_device->init(dConfig);

  m_uiControler=new SevUiControler(m_device,gConfig,this);

  return true;
}
