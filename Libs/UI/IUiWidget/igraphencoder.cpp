#include "igraphencoder.h"
#include "igraphencoder_p.h"
#include "sdtglobaldef.h"
#include "iuiwidget.h"
#include "sevdevice.h"

#include <QTimer>

#define TIMER_INTERVAL 500

IGraphEncoderPrivate::IGraphEncoderPrivate():
  m_curEncConfigItem(NULL),
  m_encConfigManage(NULL),
  m_iDataBinding(NULL),
  m_updateTimer(NULL)
{

}

IGraphEncoderPrivate::~IGraphEncoderPrivate()
{

}

IGraphEncoder::IGraphEncoder(QWidget *parent) :IGraph(*(new IGraphEncoderPrivate),parent)
{
  Q_D(IGraphEncoder);
  d->m_updateTimer=new QTimer;
  d->m_updateTimer->setInterval(TIMER_INTERVAL);
  connect(d->m_updateTimer,SIGNAL(timeout()),this,SLOT(onUpdateTimeOut()));
}
IGraphEncoder::~IGraphEncoder()
{
  Q_D(IGraphEncoder);
  GT::deletePtrObject(d->m_updateTimer);
}
void IGraphEncoder::startUpdateTimer(bool enabled)
{
  Q_D(IGraphEncoder);
  if(enabled)
    d->m_updateTimer->start();
  else
    d->m_updateTimer->stop();
}

IGraphEncoder::IGraphEncoder(IGraphEncoderPrivate &dd, QWidget *parent):IGraph(dd,parent)
{
  Q_D(IGraphEncoder);
  d->m_updateTimer=new QTimer;
  d->m_updateTimer->setInterval(TIMER_INTERVAL);
  connect(d->m_updateTimer,SIGNAL(timeout()),this,SLOT(onUpdateTimeOut()));
}

qint32 IGraphEncoder::readPos(const QString &key)
{
  Q_D(IGraphEncoder);
  bool isOk=true;
  qint32 pos=0;
  pos=d->m_dev->genCmdRead(key,d->m_uiWidget->uiIndexs().axisInx,isOk);
  return pos;
}

qint32 IGraphEncoder::readPosInput(const QString &key)
{
  Q_D(IGraphEncoder);
  bool isOk=true;
  qint32 pos=0;
  pos=d->m_dev->genCmdRead(key,d->m_uiWidget->uiIndexs().axisInx,isOk);
  return pos;
}

qint32 IGraphEncoder::readPosOffset(const QString &key)
{
  Q_D(IGraphEncoder);
  bool isOk=true;
  qint32 pos=0;
  pos=d->m_dev->genCmdRead(key,d->m_uiWidget->uiIndexs().axisInx,isOk);
  return pos;
}

quint16 IGraphEncoder::readPPN(const QString &key)
{
  Q_D(IGraphEncoder);
  bool isOk=true;
  quint16 ppn=0;
  ppn=d->m_dev->genCmdRead(key,d->m_uiWidget->uiIndexs().axisInx,isOk);
  return ppn;
}

quint16 IGraphEncoder::readSeqDir(const QString &key)
{
  Q_D(IGraphEncoder);
  bool isOk=true;
  quint16 dir=0;
  dir=d->m_dev->genCmdRead(key,d->m_uiWidget->uiIndexs().axisInx,isOk);
  return dir;
}

quint16 IGraphEncoder::readEncInfo(const QString &key)
{
  Q_D(IGraphEncoder);
  bool isOk=true;
  quint16 info=0;
  info=d->m_dev->genCmdRead(key,d->m_uiWidget->uiIndexs().axisInx,isOk);
  return info;
}

quint16 IGraphEncoder::readErrLost(const QString &key)
{
  Q_D(IGraphEncoder);
  bool isOk=true;
  quint16 err=0;
  err=d->m_dev->genCmdRead(key,d->m_uiWidget->uiIndexs().axisInx,isOk);
  return err;
}
