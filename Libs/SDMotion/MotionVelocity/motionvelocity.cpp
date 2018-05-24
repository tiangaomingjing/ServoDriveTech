#include "motionvelocity.h"
#include "imotion_p.h"
#include "uimotionvelocity.h"
#include "sevdevice.h"
#include "vmotionthread.h"
#include "Option"

#include <QDebug>

class MotionVelocityPrivate:public IMotionPrivate
{
  Q_DECLARE_PUBLIC(MotionVelocity)
public:
  MotionVelocityPrivate(){}
  ~MotionVelocityPrivate(){}
protected:
  VmotionThread *m_vThread;
};

MotionVelocity::MotionVelocity(QListWidget *axisListWidget,SevDevice *sev, const QString &name, QObject *parent):
  IMotion(*(new MotionVelocityPrivate),parent)
{
  Q_D(MotionVelocity);
  setSevDevice(sev);
  setMotionType(MOTION_TYPE_VEL);
  setName(name);

  d->m_axisListWidget = axisListWidget;
  UiMotionVelocity *uivel = new UiMotionVelocity(this,0);
  d->m_ui = uivel;
  d->m_vThread = new VmotionThread(sev,uivel->uiDataList());

}

MotionVelocity::~MotionVelocity()
{
  Q_D(MotionVelocity);
  delete d->m_vThread;
  delete d->m_ui ;
}

bool MotionVelocity::move(quint16 axisInx)
{
  Q_D(MotionVelocity);
  qDebug()<<"Velocity Axis "<<axisInx<<"Move";
  if(d->m_vThread->isRunning() == false)
  {
    d->m_vThread->start();
    d->m_vThread->setPriority(QThread::TimeCriticalPriority);
  }
  UiMotionData *data = UiMotion()->m_uiDataList.at(axisInx);

  data->m_lock.lockForWrite();

  data->m_currentCount = 0;
  data->m_curTimeout = 0;
  data->m_seqCircleUse = 0;
  data->m_start = true;
  data->m_delayStartCount = optPlot()->delayTime()/d->m_vThread->msdelayTime();
  data->m_runSta = UiMotionData::RUN_STA_INIT;

  data->m_lock.unlock();

  return true;
}

bool MotionVelocity::stop(quint16 axisInx)
{
  qDebug()<<"Velocity Axis "<<axisInx<<"Stop";
  return true;
}

UiMotionVelocity * MotionVelocity::UiMotion()
{
  Q_D(MotionVelocity);
  UiMotionVelocity *ui = qobject_cast<UiMotionVelocity *>(d->m_ui);
  return ui;
}

void MotionVelocity::updateAxisUi(quint16 axisInx)
{
  UiMotionVelocity *ui = UiMotion();
  ui->updataUi(axisInx);
}

