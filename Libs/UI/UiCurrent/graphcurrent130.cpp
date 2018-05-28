#include "graphcurrent130.h"

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


class GraphCurrent130Private:public IGraphCurrentPrivate
{
  Q_DECLARE_PUBLIC(GraphCurrent130)
public:
  GraphCurrent130Private(){}
  ~GraphCurrent130Private(){}
};

GraphCurrent130::GraphCurrent130(QWidget *parent) :
  IGraphCurrent(*(new GraphCurrent130Private),parent)
{

}

GraphCurrent130::~GraphCurrent130()
{
//  delete ui;
  qDebug()<<"GraphCurrent130 destruct-->";
}

void GraphCurrent130::setCustomVisitActive(IUiWidget *uiWidget)
{
  Q_UNUSED(uiWidget);
}
void GraphCurrent130::setUiVersionName()
{
  Q_D(GraphCurrent130);
  d->m_versionName="V130";
  setObjectName("GraphCurrent130");
}

void GraphCurrent130::setupDataMappings()
{
  Q_D(GraphCurrent130);

  d->m_mapping->insertBox2MultiItem(d->m_pEdit,d->m_treeWidget->topLevelItem(FND_INX));
  d->m_mapping->insertBox2MultiItem(d->m_pEdit,d->m_treeWidget->topLevelItem(FNQ_INX));
  d->m_mapping->insertBox2MultiItem(d->m_iEdit,d->m_treeWidget->topLevelItem(TID_INX));
  d->m_mapping->insertBox2MultiItem(d->m_iEdit,d->m_treeWidget->topLevelItem(TIQ_INX));

  d->m_mapping->insertBox2Item(d->m_pEdit,d->m_treeWidget->topLevelItem(FNQ_INX));
  d->m_mapping->insertBox2Item(d->m_iEdit,d->m_treeWidget->topLevelItem(TIQ_INX));

  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(TIQ_INX),d->m_iEdit);
  d->m_mapping->insertItem2Box(d->m_treeWidget->topLevelItem(FNQ_INX),d->m_pEdit);
}

void GraphCurrent130::createPidControllerItem()
{
  Q_D(GraphCurrent130);

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
  d->m_scene->addItem(d->m_UPID);//take ownership
}


