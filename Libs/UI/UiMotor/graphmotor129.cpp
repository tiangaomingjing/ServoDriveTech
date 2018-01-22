#include "graphmotor129.h"
#include "ui_graphmotor129.h"
#include "igraphmotor_p.h"
#include "iuiwidget.h"
#include "uimotor.h"
#include "sevdevice.h"

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
void GraphMotor129::accept(IUiWidget *ui)
{
  Q_D(GraphMotor129);

  qDebug()<<"graph motor 129 accept"<<ui->objectName();
  d->m_dev=ui->device();
  int axis=ui->uiIndexs().axisInx;
  int page=ui->uiIndexs().pageInx;
  d->m_treeWidget=d->m_dev->axisTreeSource(axis,page);
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
      d->m_treeWidget->topLevelItem(0)->setText(1,QString::number(ui->dspinBox_fcoe->value()));
    }
  }
  return QWidget::eventFilter(obj,event);
}
