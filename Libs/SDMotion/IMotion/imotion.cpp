#include "imotion.h"
#include "imotion_p.h"
#include "sevdevice.h"
#include "Option"
#include <QLabel>
#include <QDebug>

IMotion::~IMotion()
{
  delete d_ptr;
  qDebug()<<"IMotion destruct -->";
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

QListWidget *IMotion::axisListWidget()
{
  Q_D(IMotion);
  return d->m_axisListWidget;
}

IMotion::MotionType IMotion::motionType()
{
  Q_D(IMotion);
  return d->m_type;
}

OptPlot *IMotion::optPlot()
{
  OptPlot *plot = dynamic_cast<OptPlot *>(OptContainer::instance()->optItem("optplot"));
  return plot;
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

MotionNone::MotionNone(QListWidget *axisListWidget,SevDevice *sev, const QString &name, QObject *parent):
  IMotion(*(new MotionNonePrivate),parent)
{
  Q_D(MotionNone);
  setName(name);
  setMotionType(MOTION_TYPE_NONE);
  QLabel *label = new QLabel(tr("please select motion"));
  label->setAlignment(Qt::AlignCenter);
  d->m_ui = label;
  d->m_axisListWidget = axisListWidget;
}

MotionNone::~MotionNone()
{
  Q_D(MotionNone);
  delete d->m_ui;
}

void MotionNone::movePrepare(quint16 axisInx)
{
  Q_UNUSED(axisInx)
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
