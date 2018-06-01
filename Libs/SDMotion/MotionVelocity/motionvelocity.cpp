#include "motionvelocity.h"
#include "imotion_p.h"
#include "uimotionvelocity.h"
#include "sevdevice.h"
#include "velplanmotion.h"
#include "Option"

#include <QDebug>
#include <QListWidget>

class MotionVelocityPrivate:public IMotionPrivate
{
  Q_DECLARE_PUBLIC(MotionVelocity)
public:
  MotionVelocityPrivate(){}
  ~MotionVelocityPrivate(){}
protected:
  QList<VelPlanMotion *>m_velPlanList;

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
  for(int i = 0;i<sev->axisNum();i++)
  {
    VelPlanMotion *vel = new VelPlanMotion(i,sev,uivel->uiDataList().at(i));
    d->m_velPlanList.append(vel);
    connect(vel,SIGNAL(motionFinish(quint16)),this,SLOT(onMotionFinish(quint16)));
    connect(vel,SIGNAL(progressValueChanged(quint16,int)),this,SIGNAL(progressValueChanged(quint16,int)));
  }
  d->m_motionUnFinishVector.clear();
}

MotionVelocity::~MotionVelocity()
{
  Q_D(MotionVelocity);
  GT::deepClearList(d->m_velPlanList);
  delete d->m_ui ;
}

void MotionVelocity::movePrepare(quint16 axisInx)
{
  Q_D(MotionVelocity);
  d->m_velPlanList.at(axisInx)->movePrepare();
  d->m_motionUnFinishVector.clear();
  qDebug()<<"axis "<<axisInx<<"prepare to go";
}

bool MotionVelocity::move(quint16 axisInx)
{
  Q_D(MotionVelocity);
  qDebug()<<"Velocity Axis "<<axisInx<<"Move";

  if(false == d->m_sev->axisServoIsOn(axisInx))
    return false ;

  d->m_motionUnFinishVector.append(axisInx);

  d->m_velPlanList.at(axisInx)->move();
  d->m_ui->setEnabled(false);//Ui不能编辑
  return true;
}

bool MotionVelocity::stop(quint16 axisInx)
{
  Q_D(MotionVelocity);
  qDebug()<<"Velocity Axis "<<axisInx<<"Stop";
  d->m_velPlanList.at(axisInx)->stop();
  d->m_ui->setEnabled(true);
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

void MotionVelocity::onMotionFinish(quint16 axisInx)
{
  Q_D(MotionVelocity);
  if(d->m_axisListWidget->currentRow() == axisInx)
     d->m_ui->setEnabled(true);

  emit motionFinish(axisInx);

  d->m_motionUnFinishVector.removeOne(axisInx);
  if(d->m_motionUnFinishVector.isEmpty())
    emit motionAllDone();
}

