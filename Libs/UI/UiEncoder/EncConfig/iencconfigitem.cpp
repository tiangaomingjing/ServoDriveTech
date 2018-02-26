#include "iencconfigitem.h"

#include <QDebug>

IEncConfigItem::IEncConfigItem(QObject *parent) : QObject(parent),
  m_encType(ENC_TYPE_ABSOLUTE),
  m_encConfigData(0x0000),
  m_lineNumber(131072),
  m_lostOper(0x0020),
  m_alarmOper(0x1fff),
  m_crcErrOper(0x7F00),
  m_attributeUi(NULL)
{
  m_warnings<<tr("0 when power shut down ,the battery capacity is low ")
            <<tr("1 battery capacity is low")
           <<tr("2 position error,absolute and mutil value is not the same")
          <<tr("3 encoder of mutil communication error")
         <<tr("4 absolute position error is over threshold")
        <<tr("5 speed exception")
       <<tr("6 the base board of encoder is over temperature")
      <<tr("7 speed over when open power")
     <<tr("8 mutil value overflow")
    <<tr("9 encoder memery access exception")
   <<tr("10 encoder memery accessing...")
  <<tr("11 position error,absolute is not equal to increase")
  <<tr("12 single absolute value working now....");
  setObjectName(tr("IEncConfig"));
}
IEncConfigItem::~IEncConfigItem()
{

}
QStringList IEncConfigItem::errorStrings(quint16 errorCode)
{
  quint16 almCode;
  QStringList list;
  quint16 oper=0x0001;
  quint16 andValue=0x0000;
  almCode=errorCode&m_alarmOper;
  for(int i=0;i<m_warnings.count();i++)
  {
      andValue=oper<<i;
      if(almCode&andValue)
          list.append(m_warnings.at(i));
  }
  return list;
}

bool IEncConfigItem::hasWarnig(quint16 errorCode)
{
  return ((errorCode&m_alarmOper)>0);
}

bool IEncConfigItem::hasLostError(quint16 errorCode)
{
  return ((errorCode&m_lostOper)>0);
}
void IEncConfigItem::createAttributeUi()
{
  m_attributeUi=NULL;
}
bool IEncConfigItem::execute()
{
  qDebug()<<"m_encConfigData"<<m_encConfigData;
  return true;
}

IEncConfigItem::EncType IEncConfigItem::encType() const
{
  return m_encType;
}

void IEncConfigItem::setEncType(const EncType encType)
{
  m_encType = encType;
}

quint16 IEncConfigItem::encConfigData() const
{
  return m_encConfigData;
}

void IEncConfigItem::setEncConfigData(const quint16 encConfigData)
{
  m_encConfigData = encConfigData;
}

quint32 IEncConfigItem::lineNumber() const
{
  return m_lineNumber;
}

void IEncConfigItem::setLineNumber(const quint32 lineNumber)
{
  m_lineNumber = lineNumber;
}

quint16 IEncConfigItem::lostOper() const
{
  return m_lostOper;
}

void IEncConfigItem::setLostOper(const quint16 lostOper)
{
  m_lostOper = lostOper;
}

quint16 IEncConfigItem::alarmOper() const
{
  return m_alarmOper;
}

void IEncConfigItem::setAlarmOper(const quint16 alarmOper)
{
  m_alarmOper = alarmOper;
}

QWidget *IEncConfigItem::attributeUi() const
{
  return m_attributeUi;
}

void IEncConfigItem::setWarningsString(const QStringList &warnings)
{
  m_warnings.clear();
  m_warnings = warnings;
}

quint16 IEncConfigItem::crcErrOper() const
{
  return m_crcErrOper;
}

void IEncConfigItem::setCrcErrOper(const quint16 crcErrOper)
{
  m_crcErrOper = crcErrOper;
}

