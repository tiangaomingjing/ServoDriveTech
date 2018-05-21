#include "imotion.h"
#include "imotion_p.h"

IMotion::~IMotion()
{
  delete d_ptr;
}

QWidget *IMotion::ui()
{
  Q_D(IMotion);
  return d->m_ui;
}

void IMotion::setUi(QWidget *ui)
{
  Q_D(IMotion);
  d->m_ui = ui;
}

void IMotion::setName(const QString &name)
{
  Q_D(IMotion);
  d->m_name = name;
}

QString IMotion::name()
{
  Q_D(IMotion);
  return d->m_name;
}

SevDevice *IMotion::sevDevice()
{
  Q_D(IMotion);
  return d->m_sev;
}

void IMotion::setSevDevice(SevDevice *sev)
{
  Q_D(IMotion);
  d->m_sev = sev;
}

void IMotion::setMotionType(IMotion::MotionType type)
{
  Q_D(IMotion);
  d->m_type = type;
}

IMotion::MotionType IMotion::motionType()
{
  Q_D(IMotion);
  return d->m_type;
}

IMotion::IMotion(IMotionPrivate &dd, QObject *parent):d_ptr(&dd),QObject(parent)
{
  d_ptr->q_ptr = this;
}

class MotionNonePrivate:public IMotionPrivate
{
  Q_DECLARE_PUBLIC(MotionNone)
public:
  MotionNonePrivate(){}
  ~MotionNonePrivate(){}
};

MotionNone::MotionNone(SevDevice *sev, MotionType type,const QString &name, QObject *parent):
  IMotion(*(new MotionNonePrivate),parent)
{
  Q_UNUSED(sev)
  setName(name);
  setMotionType(type);
}

bool MotionNone::move(quint16 axisInx)
{
  Q_UNUSED(axisInx)
  return false;
}
