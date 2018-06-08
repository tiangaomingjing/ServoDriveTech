#include "graphcurrent129.h"
#include "ui_graphcurrent129.h"
#include "igraphcurrent_p.h"
#include "Option"
#include "iuiwidget.h"
#include "boxitemmapping.h"
#include "sevdevice.h"
#include "SDTGraphicsItems/SDTGraphicsItems"

#include <QDebug>
#include <QTreeWidget>
#include <QDoubleSpinBox>

#define TID_INX 0
#define TIQ_INX 1
#define FND_INX 2
#define FNQ_INX 3


class GraphCurrent129Private:public IGraphCurrentPrivate
{
  Q_DECLARE_PUBLIC(GraphCurrent129)
public:
  GraphCurrent129Private(){}
  ~GraphCurrent129Private(){}
};

GraphCurrent129::GraphCurrent129(QWidget *parent) :
  IGraphCurrent(*(new GraphCurrent129Private),parent)
//  ui(new Ui::GraphCurrent129)
{
//  ui->setupUi(this);
}

GraphCurrent129::~GraphCurrent129()
{
//  delete ui;

//  qDebug()<<"GraphCurrent129 destruct-->";
}

void GraphCurrent129::setCustomVisitActive(IUiWidget *uiWidget)
{
  Q_UNUSED(uiWidget);
}
void GraphCurrent129::setUiVersionName()
{
  Q_D(GraphCurrent129);
  d->m_versionName="V129";
  setObjectName("GraphCurrent129");
}

void GraphCurrent129::setupDataMappings()
{
  Q_D(GraphCurrent129);

  d->m_mapping->insertBox2MultiItem(d->m_pEdit,d->m_treeWidget->topLevelItem(FND_INX));
  d->m_mapping->insertBox2MultiItem(d->m_pEdit,d->m_treeWidget->topLevelItem(FNQ_INX));
  d->m_mapping->insertBox2MultiItem(d->m_iEdit,d->m_treeWidget->topLevelItem(TID_INX));
  d->m_mapping->insertBox2MultiItem(d->m_iEdit,d->m_treeWidget->topLevelItem(TIQ_INX));

  d->m_mapping->insertBox2Item(d->m_pEdit,d->m_treeWidget->topLevelItem(FNQ_INX));
  d->m_mapping->insertBox2Item(d->m_iEdit,d->m_treeWidget->topLevelItem(TIQ_INX));

  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(TID_INX),d->m_iEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(FND_INX),d->m_pEdit);
}



