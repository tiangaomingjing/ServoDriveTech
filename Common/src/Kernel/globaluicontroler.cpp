#include "globaluicontroler.h"
#include "sdtglobaldef.h"
#include "iuiwidget.h"
#include "plotunitgraph129.h"
#include "UiPlot/uiplot.h"

#include <QDebug>

GlobalUiControler::GlobalUiControler(QList<SevDevice *> &sevList, QObject *parent):IUiControler(parent),
  m_sevList(sevList)
{

}

GlobalUiControler::~GlobalUiControler()
{
  qDebug()<<"GlobalUiControler-->destruct";
  GT::deepClearList(m_uiLists);
}

void GlobalUiControler::createUis()
{
  // 当前全局的ui只有绘图
  //如果以后要动态增加其它的ui，可以再做个配置表来实现，根据类名生成对象机制(目前没有这个必要)

  IUiWidget *uiPlot=new UiPlot;
  uiPlot->init(NULL);
  IPlotUnit *iplot=new PlotUnitGraph129(m_sevList);
  uiPlot->accept(iplot);//take ownership of iplot
  connect(this,SIGNAL(sevDeviceListChanged(QList<SevDevice*>)),iplot,SLOT(onSevDeviceListChanged(QList<SevDevice*>)));
  connect(this,SIGNAL(appClosed()),iplot,SLOT(onAppClosed()));
  m_uiLists.append(uiPlot);
}

IUiWidget *GlobalUiControler::uiWidget(const QString &name)
{
  IUiWidget *ui=NULL;
  IUiWidget *w=NULL;
  for(int i=0;i<m_uiLists.size();i++)
  {
    w=m_uiLists.at(i);
    if(w->objectName()==name)
    {
      ui=w;
      break;
    }
  }
  return ui;
}

void GlobalUiControler::setSevDeviceList(const QList<SevDevice *> &sevList)
{
  m_sevList=sevList;
  emit sevDeviceListChanged(sevList);
}
