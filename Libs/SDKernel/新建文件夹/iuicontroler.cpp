#include "iuicontroler.h"
#include "sdtglobaldef.h"

#include <QDebug>

IUiControler::IUiControler(GlobalConfig *gconfig, QObject *parent):QObject(parent),m_gConfig(gconfig)
{

}
IUiControler::~IUiControler()
{
  qDebug()<<"IUiControler-->destruct";

}
quint16 IUiControler::uiCount()
{
  return m_uiLists.count();
}

IUiWidget* IUiControler::uiAt(quint8 index)
{
  if(index>m_uiLists.count()-1)
    return NULL;
  return m_uiLists.at(index);
}
