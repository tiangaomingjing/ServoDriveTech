#include "uimotionvelocity.h"
#include "ui_uimotionvelocity.h"
#include "gtutils.h"
#include "Option"

#define PIC_NAME_VSTEP          "plot_vstep.png"
#define PIC_NAME_VSEQ           "plot_vseq.png"

UiMotionVelocity::UiMotionVelocity(int axisCount, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::UiMotionVelocity),
  m_axisCount(axisCount)
{
  ui->setupUi(this);
  ui->stackedWidget_vel_plan->setCurrentIndex(0);

  for(int i = 0;i<axisCount;i++)
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
  connect(ui->checkBox_circleSw,SIGNAL(clicked(bool)),this,SLOT(onCheckBoxCircleSWClicked()));
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
  }
  else
  {
    ui->checkBox_circleSw->setChecked(false);
    ui->stackedWidget_vel_plan->setCurrentIndex(0);
    ui->spinBox_step_amp->setValue(data->m_stepAmp);
    ui->spinBox_step_time->setValue(data->m_stepTime);
  }
}

bool UiMotionVelocity::eventFilter(QObject *obj, QEvent *event)
{

}

void UiMotionVelocity::onCheckBoxCircleSWClicked()
{
  if(ui->checkBox_circleSw->isChecked())
    ui->stackedWidget_vel_plan->setCurrentIndex(1);
  else
    ui->stackedWidget_vel_plan->setCurrentIndex(0);
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

