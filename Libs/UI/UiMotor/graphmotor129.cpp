#include "graphmotor129.h"
#include "ui_graphmotor129.h"
#include "igraphmotor_p.h"
#include "iuiwidget.h"
#include "uimotor.h"
#include "sevdevice.h"
#include "boxitemmapping.h"

#include <QDebug>
#include <QTreeWidget>
#include <QKeyEvent>

class GraphMotor129Private:public IGraphMotorPrivate
{
  Q_DECLARE_PUBLIC(GraphMotor129)
public:
  GraphMotor129Private(){}
  ~GraphMotor129Private(){}
};

GraphMotor129::GraphMotor129(QWidget *parent) :
  IGraphMotor(*(new GraphMotor129Private),parent),
  ui(new Ui::GraphMotor129)
{
  ui->setupUi(this);
//  QGridLayout *glayout=new QGridLayout(this);
////  glayout->addWidget(ui->pushButton,0,2);
//  glayout->addLayout(ui->hlayout_btn,0,0);
//  glayout->addWidget(ui->widget_currentPrm,1,0);
//  glayout->addWidget(ui->widget_machinePrm,1,1,1,2);
//  glayout->addWidget(ui->widget_velocityPrm,2,0);
//  glayout->addWidget(ui->widget_impedancePrm,2,1);
//  glayout->addWidget(ui->widget_torquePrm,2,2);

  QList<QDoubleSpinBox *> allBox = findChildren<QDoubleSpinBox *>();
  qDebug()<<"all box count="<<allBox.count();
  foreach (QDoubleSpinBox *box, allBox) {
    box->installEventFilter(this);
  }

}

GraphMotor129::~GraphMotor129()
{
  delete ui;
}
void GraphMotor129::visit(IUiWidget *ui)
{
  Q_D(GraphMotor129);

  qDebug()<<"graph motor 129 visit"<<ui->objectName();
  d->m_dev=ui->device();
  int axis=ui->uiIndexs().axisInx;
  int page=ui->uiIndexs().pageInx;
  d->m_treeWidget=d->m_dev->axisTreeSource(axis,page);

  d->m_mapping->insertBox2Item(this->ui->dspinBox_iRat,d->m_treeWidget->topLevelItem(0));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_iMax,d->m_treeWidget->topLevelItem(1));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_vRat,d->m_treeWidget->topLevelItem(2));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_vOver,d->m_treeWidget->topLevelItem(3));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_vMax,d->m_treeWidget->topLevelItem(4));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_torque,d->m_treeWidget->topLevelItem(5));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_pole,d->m_treeWidget->topLevelItem(6));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_maxVoltage,d->m_treeWidget->topLevelItem(7));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_phim,d->m_treeWidget->topLevelItem(8));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_ldm,d->m_treeWidget->topLevelItem(9));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_lqm,d->m_treeWidget->topLevelItem(10));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_rm,d->m_treeWidget->topLevelItem(11));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_Jm,d->m_treeWidget->topLevelItem(12));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_JmPercent,d->m_treeWidget->topLevelItem(13));
  d->m_mapping->insertBox2Item(this->ui->dspinBox_fcoe,d->m_treeWidget->topLevelItem(14));
}
bool GraphMotor129::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type()==QEvent::KeyPress)
  {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
    {
      Q_D(GraphMotor129);

//      if(obj==ui->dsp)
      qDebug()<<"enter clicked"<<"object name"<<obj->objectName();
      d->m_mapping->syncBoxText2Item(static_cast<QDoubleSpinBox*>(obj));
    }
  }
  return QWidget::eventFilter(obj,event);
}
