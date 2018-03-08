#include "graphmotor129.h"
#include "ui_graphmotor129.h"
#include "igraphmotor_p.h"
#include "iuiwidget.h"
#include "uimotor.h"
#include "sevdevice.h"
#include "boxitemmapping.h"
#include "Option"

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

}

GraphMotor129::~GraphMotor129()
{
  delete ui;
}
void GraphMotor129::syncTreeDataToUiFace()
{
  //将树的数据全更新到用户界面上
  Q_D(GraphMotor129);
  d->m_mapping->syncAllItem2BoxText();
}

void GraphMotor129::setCustomVisitActive(IUiWidget *uiWidget)
{
  Q_D(GraphMotor129);
  Q_UNUSED(uiWidget);
  this->ui->dspinBox_maxVoltage->setEnabled(false);
}
void GraphMotor129::setUiVersionName()
{
  Q_D(GraphMotor129);
  d->m_versionName="V129";
}

void GraphMotor129::setupDataMappings()
{
  Q_D(GraphMotor129);

  QList<QDoubleSpinBox *>bList;
  //bList的先后位置不能变
  bList<<ui->dspinBox_iRat\
      <<ui->dspinBox_iMax\
     <<ui->dspinBox_vRat\
    <<ui->dspinBox_vOver\
   <<ui->dspinBox_vMax\
  <<ui->dspinBox_torque\
  <<ui->dspinBox_pole\
  <<ui->dspinBox_maxVoltage\
  <<ui->dspinBox_phim\
  <<ui->dspinBox_ldm\
  <<ui->dspinBox_lqm\
  <<ui->dspinBox_rm\
  <<ui->dspinBox_Jm\
  <<ui->dspinBox_JmPercent\
  <<ui->dspinBox_fcoe;

  if(bList.count()<=d->m_treeWidget->topLevelItemCount())
  {
    for(int i=0;i<bList.count();i++)
    {
      d->m_mapping->insertBox2Item(bList.at(i),d->m_treeWidget->topLevelItem(i));
      d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(i),bList.at(i));
    }
  }
}


void GraphMotor129::onDoubleSpinBoxFocusOut()
{
  Q_D(GraphMotor129);
  QDoubleSpinBox *box=qobject_cast<QDoubleSpinBox *>(sender());
  QTreeWidgetItem *item=d->m_mapping->item(box);
  d->m_mapping->syncItem2BoxText(item);
  qDebug()<<"focus out"<<box;
}

