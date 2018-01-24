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
void GraphMotor129::visitActive(IUiWidget *uiWidget)
{
  Q_D(GraphMotor129);

  qDebug()<<"graph motor 129 visit"<<uiWidget->objectName();
  d->m_dev=uiWidget->device();
  int axis=uiWidget->uiIndexs().axisInx;
  int page=uiWidget->uiIndexs().pageInx;
  d->m_treeWidget=d->m_dev->axisTreeSource(axis,page);

  this->ui->dspinBox_maxVoltage->setEnabled(false);

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
void GraphMotor129::setUiVersionName()
{
  Q_D(GraphMotor129);
  d->m_versionName="V129";
}
bool GraphMotor129::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type()==QEvent::KeyPress)
  {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
    {
      Q_D(GraphMotor129);
      qDebug()<<"enter clicked"<<"object name"<<obj->objectName();
      d->m_mapping->syncBoxText2Item(static_cast<QDoubleSpinBox*>(obj));
      return true;
    }
  }
  return QWidget::eventFilter(obj,event);
}
