#include "imotion.h"
#include "imotion_p.h"
#include <QLabel>
#include <QDebug>

IMotion::~IMotion()
{
  delete d_ptr;
}

QWidget *IMotion::ui()
{
  Q_D(IMotion);
  return d->m_ui;
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

IMotion::MotionType IMotion::motionType()
{
  Q_D(IMotion);
  return d->m_type;
}

IMotion::IMotion(IMotionPrivate &dd, QObject *parent):d_ptr(&dd),QObject(parent)
{
  d_ptr->q_ptr = this;
}

void IMotion::setMotionType(IMotion::MotionType type)
{
  Q_D(IMotion);
  d->m_type = type ;
}

class MotionNonePrivate:public IMotionPrivate
{
  Q_DECLARE_PUBLIC(MotionNone)
public:
  MotionNonePrivate(){}
  ~MotionNonePrivate(){}
};

MotionNone::MotionNone(SevDevice *sev, const QString &name, QObject *parent):
  IMotion(*(new MotionNonePrivate),parent)
{
  Q_D(MotionNone);
  Q_UNUSED(sev)
  setName(name);
  setMotionType(MOTION_TYPE_NONE);
  QLabel *label = new QLabel(tr("please select motion"));
  label->setAlignment(Qt::AlignCenter);
  d->m_ui = label;
}

MotionNone::~MotionNone()
{
  Q_D(MotionNone);
  delete d->m_ui;
}

bool MotionNone::move(quint16 axisInx)
{
  Q_UNUSED(axisInx)
  qDebug()<<"None Axis "<<axisInx<<"Move";
  return true;
}

bool MotionNone::stop(quint16 axisInx)
{
  Q_UNUSED(axisInx)
  qDebug()<<"None Axis "<<axisInx<<"Stop";
  return true;
}

void MotionNone::updateAxisUi(quint16 axisInx)
{
  Q_UNUSED(axisInx)
}
