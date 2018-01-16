#include "iuicontroler.h"
#include "sdtglobaldef.h"

#include "Option"

#include <QDebug>

IUiControler::IUiControler(QObject *parent):QObject(parent)
{
  m_optc=OptContainer::instance();
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
