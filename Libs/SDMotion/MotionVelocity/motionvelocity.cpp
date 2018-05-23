#include "motionvelocity.h"
#include "imotion_p.h"
#include "uimotionvelocity.h"
#include "sevdevice.h"

#include <QDebug>

class MotionVelocityPrivate:public IMotionPrivate
{
  Q_DECLARE_PUBLIC(MotionVelocity)
public:
  MotionVelocityPrivate(){}
  ~MotionVelocityPrivate(){}
protected:

};

MotionVelocity::MotionVelocity(SevDevice *sev, const QString &name, QObject *parent):
  IMotion(*(new MotionVelocityPrivate),parent)
{
  Q_D(MotionVelocity);
  setSevDevice(sev);
  setMotionType(MOTION_TYPE_VEL);
  setName(name);

  d->m_ui = new UiMotionVelocity(sev->axisNum(),0);

}

MotionVelocity::~MotionVelocity()
{
  Q_D(MotionVelocity);
  delete d->m_ui ;
}

bool MotionVelocity::move(quint16 axisInx)
{
  Q_UNUSED(axisInx)
  qDebug()<<"Velocity Axis "<<axisInx<<"Move";
  return true;
}

bool MotionVelocity::stop(quint16 axisInx)
{
  qDebug()<<"Velocity Axis "<<axisInx<<"Stop";
  return true;
}

void MotionVelocity::updateAxisUi(quint16 axisInx)
{
  Q_D(MotionVelocity);
  UiMotionVelocity *ui = qobject_cast<UiMotionVelocity *>(d->m_ui);
  ui->updataUi(axisInx);
}

