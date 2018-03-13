#include "graphposition129.h"
//#include "ui_graphposition129.h"
#include "igraphposition_p.h"
#include "boxitemmapping.h"

#include <QTreeWidgetItem>
#include <QDebug>

#define FN_FST_6_INX 0
#define ABS_RAT_6_INX 1
#define POS_RAT_6_INX 2
#define NEG_RAT_6_INX 3
#define KGV_6_INX 4
#define KGA_6_INX 5

class GraphPosition129Private:public IGraphPositionPrivate
{
  Q_DECLARE_PUBLIC(GraphPosition129)
public:
  GraphPosition129Private(){}
  ~GraphPosition129Private(){qDebug()<<"GraphPosition129Private destruct-->";}
};

GraphPosition129::GraphPosition129(QWidget *parent) :
  IGraphPosition(*(new GraphPosition129Private),parent)
//  ui(new Ui::GraphPosition129)
{
//  ui->setupUi(this);
}

GraphPosition129::~GraphPosition129()
{
//  delete ui;
  qDebug()<<"GraphPosition129 destruct-->";

}
void GraphPosition129::setCustomVisitActive(IUiWidget *uiWidget)
{
  Q_UNUSED(uiWidget);
}

void GraphPosition129::setupDataMappings()
{
  Q_D(GraphPosition129);

  d->m_mapping->insertBox2Item(d->m_pEdit,d->m_treeWidget->topLevelItem(FN_FST_6_INX));
  d->m_mapping->insertBox2Item(d->m_accEdit,d->m_treeWidget->topLevelItem(KGA_6_INX));
  d->m_mapping->insertBox2Item(d->m_velEdit,d->m_treeWidget->topLevelItem(KGV_6_INX));

  d->m_mapping->insertBox2Item(d->m_maxvelEdit,d->m_treeWidget->topLevelItem(ABS_RAT_6_INX));
  d->m_mapping->insertBox2Item(d->m_maxvelEdit_P,d->m_treeWidget->topLevelItem(POS_RAT_6_INX));
  d->m_mapping->insertBox2Item(d->m_maxvelEdit_N,d->m_treeWidget->topLevelItem(NEG_RAT_6_INX));

  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(FN_FST_6_INX),d->m_pEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(KGA_6_INX),d->m_accEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(KGV_6_INX),d->m_velEdit);

  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(ABS_RAT_6_INX),d->m_maxvelEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(POS_RAT_6_INX),d->m_maxvelEdit_P);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(NEG_RAT_6_INX),d->m_maxvelEdit_N);

}
void GraphPosition129::setUiVersionName()
{
  Q_D(GraphPosition129);
  d->m_versionName="V129";
  setObjectName("GraphPosition129");
}
