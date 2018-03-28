#include "globaluicontroler.h"
#include "sdtglobaldef.h"
#include "UiPlot/uiplot.h"
#include "IUiWidget/iuiwidget.h"

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
  //如果以后要动态增加其它的ui，可以再做个配置表来实现，根据类名生成对象机制
  IUiWidget *uiPlot=new UiPlot;
  uiPlot->init(NULL);
  m_uiLists.append(uiPlot);
}

IUiWidget *GlobalUiControler::uiWidget(const QString &name)
{
  IUiWidget *ui=NULL;
  foreach (IUiWidget *w, m_uiLists)
  {
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
}
