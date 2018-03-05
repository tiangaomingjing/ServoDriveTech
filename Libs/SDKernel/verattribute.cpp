#include "verattribute.h"
#include "deviceidhelper.h"
#include "icom.h"
#include "sevdevice.h"

#include <QDebug>

#define VERSION_THRESHOLD 128

VerAttribute::VerAttribute(QObject *parent) : QObject(parent),
  m_versionNeedChecked(false),
  m_hardIsBigger128(false)
{

}
VerAttribute::~VerAttribute()
{

}
void VerAttribute::setActive(SevDevice*sev)
{
  ComDriver::ICom *com=sev->socketCom();
  DeviceIdHelper idHelper(com);
  bool vok=true;
  quint32 hver=idHelper.readVersion(vok).remove(0,1).toUInt();
  m_hardIsBigger128=hver>VERSION_THRESHOLD?true:false;
  com->enableCRC(m_hardIsBigger128);

  quint32 sver=sev->versionName().remove(0,1).toUInt();
  bool softIsBigger128=sver>128?true:false;
  m_versionNeedChecked=(softIsBigger128&&m_hardIsBigger128);

  qDebug()<<"hard version="<<hver<<"soft version="<<sver;
  qDebug()<<"m_versionNeedChecked"<<m_versionNeedChecked;

}

bool VerAttribute::versionNeedChecked() const
{
  return m_versionNeedChecked;
}

