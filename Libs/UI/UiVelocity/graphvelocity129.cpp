#include "graphvelocity129.h"
#include "ui_graphvelocity129.h"
#include "igraphvelocity_p.h"
#include "boxitemmapping.h"
#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#define FN_FST_5_INX 0
#define TI_FST_5_INX 1
#define ABS_RAT_5_INX 2
#define POS_RAT_5_INX 3
#define NEG_RAT_5_INX 4
#define FN_SEC_5_INX 5
#define TI_SEC_5_INX 6

class GraphVelocity129Private:public IGraphVelocityPrivate
{
  Q_DECLARE_PUBLIC(GraphVelocity129)
public:
  GraphVelocity129Private(){}
  ~GraphVelocity129Private(){}

};

GraphVelocity129::GraphVelocity129(QWidget *parent) :
  IGraphVelocity(*(new GraphVelocity129Private),parent)
//  ,ui(new Ui::GraphVelocity129)
{
//  ui->setupUi(this);
}

GraphVelocity129::~GraphVelocity129()
{
//  delete ui;
  qDebug()<<"GraphVelocity129 destruct-->";
}
void GraphVelocity129::setCustomVisitActive(IUiWidget *uiWidget)
{

}
void GraphVelocity129::setUiVersionName()
{
  Q_D(GraphVelocity129);
  d->m_versionName="V129";
  setObjectName("GraphVelocity129");
}

void GraphVelocity129::setupDataMappings()
{
  Q_D(GraphVelocity129);

  d->m_mapping->insertBox2Item(d->m_pEdit,d->m_treeWidget->topLevelItem(FN_FST_5_INX));
  d->m_mapping->insertBox2Item(d->m_iEdit,d->m_treeWidget->topLevelItem(TI_FST_5_INX));

  d->m_mapping->insertBox2Item(d->m_maxTqEdit,d->m_treeWidget->topLevelItem(ABS_RAT_5_INX));
  d->m_mapping->insertBox2Item(d->m_maxTqEdit_P,d->m_treeWidget->topLevelItem(POS_RAT_5_INX));
  d->m_mapping->insertBox2Item(d->m_maxTqEdit_N,d->m_treeWidget->topLevelItem(NEG_RAT_5_INX));


  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(FN_FST_5_INX),d->m_pEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(TI_FST_5_INX),d->m_iEdit);

  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(ABS_RAT_5_INX),d->m_maxTqEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(POS_RAT_5_INX),d->m_maxTqEdit_P);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(NEG_RAT_5_INX),d->m_maxTqEdit_N);

}
