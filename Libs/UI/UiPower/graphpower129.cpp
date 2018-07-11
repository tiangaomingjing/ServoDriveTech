#include "graphpower129.h"
#include "ui_graphpower129.h"
#include "igraphpower_p.h"
#include "iuiwidget.h"
#include "uipower.h"
#include "sevdevice.h"
#include "boxitemmapping.h"
#include "Option"

#include <QDebug>
#include <QTreeWidget>
#include <QKeyEvent>

class GraphPower129Private:public IGraphPowerPrivate
{
  Q_DECLARE_PUBLIC(GraphPower129)
public:
  GraphPower129Private(){}
  ~GraphPower129Private(){}
};

GraphPower129::GraphPower129(QWidget *parent) :
  IGraphPower(*(new GraphPower129Private),parent),
  ui(new Ui::GraphPower129)
{
  ui->setupUi(this);
}

GraphPower129::~GraphPower129()
{
  delete ui;
}
void GraphPower129::syncTreeDataToUiFace()
{
  //将树的数据全更新到用户界面上
  Q_D(GraphPower129);
  d->m_mapping->syncAllItem2BoxText();
}

void GraphPower129::setCustomVisitActive(IUiWidget *uiWidget)
{
  Q_UNUSED(uiWidget);
}
void GraphPower129::setUiVersionName()
{
  Q_D(GraphPower129);
  d->m_versionName="V129";
}

void GraphPower129::setupDataMappings()
{
  Q_D(GraphPower129);

  QList<QDoubleSpinBox *>bList;
  //bList的先后位置不能变
  bList<<ui->dSpinBox_pwrBusOver\
       <<ui->dSpinBox_pwrBusUnder\
       <<ui->dSpinBox_pwrBrakeOpen\
       <<ui->dSpinBox_pwrBrakeClose\
       <<ui->dSpinBox_pwrRelayOn\
       <<ui->dSpinBox_pwrRelayOff;
  if(bList.count()<=d->m_treeWidget->topLevelItemCount())
  {
    for(int i=0;i<bList.count();i++)
    {
      d->m_mapping->insertBox2Item(bList.at(i),d->m_treeWidget->topLevelItem(i));
      d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(i),bList.at(i));
    }
  }
}



