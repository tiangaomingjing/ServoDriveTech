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
bool SdAssembly::init(const DeviceConfig *dConfig)
{
  bool ret=true;
  emit initProgressInfo(10,tr("SdAssembly init"));
  m_device=new SevDevice(this);//生命由this控制，不用显性delete
  connect(m_device,SIGNAL(initProgressInfo(int,QString)),this,SIGNAL(initProgressInfo(int,QString)));
  ret=m_device->init(dConfig);
  if(ret==false)
  {
    return ret;
  }

  qDebug()<<"new SevUiControler";
  m_uiControler=new SevUiControler(m_device,this);//生命由this控制，不用显性delete
  connect(m_uiControler,SIGNAL(initProgressInfo(int,QString)),this,SIGNAL(initProgressInfo(int,QString)));
  m_uiControler->createUis();

  return true;
}
SevDevice *SdAssembly::sevDevice()
{
  return m_device;
}

IUiControler *SdAssembly::uiControler()
{
  return m_uiControler;
}
