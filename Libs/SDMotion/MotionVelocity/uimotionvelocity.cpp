#include "uimotionvelocity.h"
#include "ui_uimotionvelocity.h"
#include "gtutils.h"
#include "Option"
#include "motionvelocity.h"
#include "sevdevice.h"

#include <QKeyEvent>
#include <QListWidget>
#include <QDebug>

#define PIC_NAME_VSTEP          "plot_vstep.png"
#define PIC_NAME_VSEQ           "plot_vseq.png"

UiMotionVelocity::UiMotionVelocity(MotionVelocity *mv, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::UiMotionVelocity),
  q_ptr(mv)
{
  ui->setupUi(this);
  ui->stackedWidget_vel_plan->setCurrentIndex(0);
  m_axisCount = mv->sevDevice()->axisNum();

  ui->spinBox_seq_amp->setValue(5);
  ui->spinBox_seq_count->setValue(10);
  ui->spinBox_seq_T->setValue(200);
  ui->spinBox_step_amp->setValue(5);
  ui->spinBox_step_time->setValue(5);

  for(int i = 0;i<m_axisCount;i++)
  {
    UiMotionData* data = new UiMotionData;
    m_uiDataList.append(data);
  }
  ui->spinBox_seq_amp->installEventFilter(this);
  ui->spinBox_seq_count->installEventFilter(this);
  ui->spinBox_seq_T->installEventFilter(this);
  ui->spinBox_step_amp->installEventFilter(this);
  ui->spinBox_step_time->installEventFilter(this);

  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  connect(face,SIGNAL(faceCssChanged(QString)),this,SLOT(onCssChanged(QString)));
  setupIcons(face->css());
  connect(ui->checkBox_circleSw,SIGNAL(clicked(bool)),this,SLOT(onCheckBoxCircleSWClicked(bool)));
  connect(ui->spinBox_seq_amp,SIGNAL(valueChanged(int)),this,SLOT(onSpinBoxValueChanged(int)));
  connect(ui->spinBox_seq_count,SIGNAL(valueChanged(int)),this,SLOT(onSpinBoxValueChanged(int)));
  connect(ui->spinBox_seq_T,SIGNAL(valueChanged(int)),this,SLOT(onSpinBoxValueChanged(int)));
  connect(ui->spinBox_step_amp,SIGNAL(valueChanged(int)),this,SLOT(onSpinBoxValueChanged(int)));
  connect(ui->spinBox_step_time,SIGNAL(valueChanged(int)),this,SLOT(onSpinBoxValueChanged(int)));
}

UiMotionVelocity::~UiMotionVelocity()
{
  delete ui;
}

void UiMotionVelocity::updataUi(int axisInx)
{
  UiMotionData*data = m_uiDataList.at(axisInx);
  if(data->m_isCircle)
  {
    ui->checkBox_circleSw->setChecked(true);
    ui->stackedWidget_vel_plan->setCurrentIndex(1);
    ui->spinBox_seq_amp->setValue(data->m_seqAmp);
    ui->spinBox_seq_T->setValue(data->m_seqPeriod);
    ui->spinBox_seq_count->setValue(data->m_seqCircleCount);
    ui->spinBox_seq_amp->setStyleSheet("color:black");
    ui->spinBox_seq_count->setStyleSheet("color:black");
    ui->spinBox_seq_T->setStyleSheet("color:black");
  }
  else
  {
    ui->checkBox_circleSw->setChecked(false);
    ui->stackedWidget_vel_plan->setCurrentIndex(0);
    ui->spinBox_step_amp->setValue(data->m_stepAmp);
    ui->spinBox_step_time->setValue(data->m_stepTime);
    ui->spinBox_step_amp->setStyleSheet("color:black");
    ui->spinBox_step_time->setStyleSheet("color:black");
  }
  if(data->m_runSta == UiMotionData::RUN_STA_RUNNING)
    setEnabled(false);
  else
    setEnabled(true);
}

QList<UiMotionData *> UiMotionVelocity::uiDataList()
{
  return m_uiDataList;
}
void UiMotionVelocity::onSpinBoxValueChanged(int value)
{
  Q_UNUSED(value);
  QSpinBox *box = qobject_cast<QSpinBox *>(sender());
  box->setStyleSheet("color:red");
}

bool UiMotionVelocity::eventFilter(QObject *obj, QEvent *event)
{
  if(event->type()==QEvent::KeyPress)
  {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
    {
      QSpinBox *sbox = dynamic_cast<QSpinBox *>(obj);
      qDebug()<<"value "<<sbox->value();
      if(obj==ui->spinBox_seq_amp||obj==ui->spinBox_seq_count||obj==ui->spinBox_seq_T)
      {
        ui->spinBox_seq_amp->setStyleSheet("color:black");
        ui->spinBox_seq_count->setStyleSheet("color:black");
        ui->spinBox_seq_T->setStyleSheet("color:black");

        for(int i=0;i<q_ptr->axisListWidget()->count();i++)
        {
          if(q_ptr->axisListWidget()->item(i)->isSelected())
          {
            m_uiDataList.at(i)->m_seqAmp = ui->spinBox_seq_amp->value();
            m_uiDataList.at(i)->m_seqCircleCount = ui->spinBox_seq_count->value();
            m_uiDataList.at(i)->m_seqPeriod = ui->spinBox_seq_T->value();
          }
        }
      }
      else if(obj==ui->spinBox_step_amp||obj==ui->spinBox_step_time)
      {
        ui->spinBox_step_amp->setStyleSheet("color:black");
        ui->spinBox_step_time->setStyleSheet("color:black");

        for(int i=0;i<q_ptr->axisListWidget()->count();i++)
        {
          if(q_ptr->axisListWidget()->item(i)->isSelected())
          {
            m_uiDataList.at(i)->m_stepAmp= ui->spinBox_step_amp->value();
            m_uiDataList.at(i)->m_stepTime = ui->spinBox_step_time->value();
          }
        }
      }
      return true;
    }
  }
  return QWidget::eventFilter(obj,event);
}

void UiMotionVelocity::onCheckBoxCircleSWClicked(bool checked)
{
  if(checked)
    ui->stackedWidget_vel_plan->setCurrentIndex(1);
  else
    ui->stackedWidget_vel_plan->setCurrentIndex(0);

  //同时选择了哪些轴，就让对应的做改变
  for(int i = 0;i<q_ptr->axisListWidget()->count();i++)
  {
    if(q_ptr->axisListWidget()->item(i)->isSelected())
    {
      m_uiDataList.at(i)->m_isCircle = checked ;
    }
  }
}

void UiMotionVelocity::onCssChanged(const QString &css)
{
  setupIcons(css);
}
void UiMotionVelocity::setupIcons(const QString &css)
{
  QString iconPath=GTUtils::customPath()+"option/style/"+css+"/icon/";

  ui->label_vplan_seq->setScaledContents(true);
  ui->label_vplan_step->setScaledContents(true);
  ui->label_vplan_seq->setPixmap(QPixmap(iconPath+PIC_NAME_VSEQ));
  ui->label_vplan_step->setPixmap(QPixmap(iconPath+PIC_NAME_VSTEP));
}

