#include "graphcurrent133.h"

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


class GraphCurrent133Private:public IGraphCurrentPrivate
{
  Q_DECLARE_PUBLIC(GraphCurrent133)
public:
  GraphCurrent133Private(){}
  ~GraphCurrent133Private(){}
};

GraphCurrent133::GraphCurrent133(QWidget *parent) :
  IGraphCurrent(*(new GraphCurrent133Private),parent)
{

}

GraphCurrent133::~GraphCurrent133()
{
//  delete ui;
  qDebug()<<"GraphCurrent133 destruct-->";
}

void GraphCurrent133::setCustomVisitActive(IUiWidget *uiWidget)
{
  Q_UNUSED(uiWidget);
}
void GraphCurrent133::setUiVersionName()
{
  Q_D(GraphCurrent133);
  d->m_versionName="V133";
  setObjectName("GraphCurrent133");
}

void GraphCurrent133::setupDataMappings()
{
  Q_D(GraphCurrent133);

  d->m_mapping->insertBox2MultiItem(d->m_pEdit,d->m_treeWidget->topLevelItem(FND_INX));
  d->m_mapping->insertBox2MultiItem(d->m_pEdit,d->m_treeWidget->topLevelItem(FNQ_INX));
  d->m_mapping->insertBox2MultiItem(d->m_iEdit,d->m_treeWidget->topLevelItem(TID_INX));
  d->m_mapping->insertBox2MultiItem(d->m_iEdit,d->m_treeWidget->topLevelItem(TIQ_INX));

  d->m_mapping->insertBox2Item(d->m_pEdit,d->m_treeWidget->topLevelItem(FNQ_INX));
  d->m_mapping->insertBox2Item(d->m_iEdit,d->m_treeWidget->topLevelItem(TIQ_INX));

  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(TID_INX),d->m_iEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(FND_INX),d->m_pEdit);
}

void GraphCurrent133::createPidControllerItem()
{
  Q_D(GraphCurrent133);

  QWidget *wpid=new QWidget;
  wpid->setObjectName("widget_currentPid");
  QVBoxLayout *vlayoutTest=new QVBoxLayout(wpid);
  QLabel *title=new QLabel(tr("PID controller"),wpid);
  title->setObjectName("label_currentTitle");
  title->setAlignment(Qt::AlignCenter);
  vlayoutTest->addWidget(title);

  QLabel *pgain=new QLabel(tr("P gain(HZ)"));
  pgain->setObjectName("label_currentPgain");
  vlayoutTest->addWidget(pgain);
  QDoubleSpinBox *pedit=new QDoubleSpinBox(wpid);
  d->m_pEdit=pedit;
  pedit->setObjectName("dspinBox_currentPedit");
  pedit->setMinimum(-32768);
  pedit->setMaximum(32767);
  pedit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  vlayoutTest->addWidget(pedit);

  QLabel *igain=new QLabel(tr("I gain(us)"),wpid);
  igain->setObjectName("label_currentIgain");
  vlayoutTest->addWidget(igain);
  QDoubleSpinBox *iedit=new QDoubleSpinBox(wpid);
  d->m_iEdit=iedit;
  iedit->setObjectName("dspinBox_currentIedit");
  iedit->setMinimum(0);
  iedit->setMaximum(65535);
  iedit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  vlayoutTest->addWidget(iedit);

  QLabel *dgain=new QLabel(tr("D gain(ms)"),wpid);
  dgain->setObjectName("label_currentDgain");
  vlayoutTest->addWidget(dgain);
  QDoubleSpinBox *dedit=new QDoubleSpinBox(wpid);
  dedit->setObjectName("dspinBox_currentDedit");
  dedit->setMinimum(0);
  dedit->setMaximum(65535);
  dedit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  vlayoutTest->addWidget(dedit);

  wpid->setLayout(vlayoutTest);

  d->m_UPID=new WidgetItem;
  d->m_UPID->setWidget(wpid,true);
  d->m_scene->addItem(d->m_UPID);

  d->m_widgetItemList.append(d->m_UPID);
}


