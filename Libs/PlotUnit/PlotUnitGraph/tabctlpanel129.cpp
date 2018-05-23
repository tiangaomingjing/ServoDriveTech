#include "tabctlpanel129.h"
#include "ui_tabctlpanel129.h"
#include "sevdevice.h"
#include "gtutils.h"
#include "Option"
#include "itabwidget.h"
#include "TabModeCtl/tabmodectl.h"
#include "TabMotion/tabmotion.h"

//#define ICON_NAME_SERVO_ON      "plot_son.png"
//#define ICON_NAME_SERVO_OFF     "plot_soff.png"
//#define PIC_NAME_VSTEP          "plot_vstep.png"
//#define PIC_NAME_VSEQ           "plot_vseq.png"

typedef enum{
  TAB_MODE,
  TAB_MOTION
}TabInx;

TabCtlPanel129::TabCtlPanel129(SevDevice *sev, QWidget *parent) : QWidget(parent),
  ui(new Ui::TabCtlPanel129),
  m_sev(sev),
  m_currentTabInx(0)
{
  ui->setupUi(this);
  while (ui->tabWidget->count()>0) {
    ui->tabWidget->removeTab(0);
  }

  ITabWidget *tab = NULL;
  tab = new TabModeCtl(tr("ModeCtl"),m_sev,0);
  m_tabWidgetList.append(tab);
  tab = new TabMotion(tr("Motion"),m_sev,0);
  m_tabWidgetList.append(tab);

  for(int i=0;i<m_tabWidgetList.size();i++)
  {
    ui->tabWidget->addTab(m_tabWidgetList.at(i),m_tabWidgetList.at(i)->name());
  }

  connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(onTabCurrentChanged(int)));
}

TabCtlPanel129::~TabCtlPanel129()
{
  GT::deepClearList(m_tabWidgetList);
  delete ui;
}

void TabCtlPanel129::updateServoStatus()
{
  if(!m_sev->isConnecting())
    return ;
  m_tabWidgetList.at(m_currentTabInx)->uiUpdate();
}

void TabCtlPanel129::onTabCurrentChanged(int inx)
{
  m_currentTabInx = inx;
}

