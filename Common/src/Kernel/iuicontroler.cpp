#include "iuicontroler.h"

#include <QDebug>

IUiControler::IUiControler(SevDevice *sev, GlobalConfig *gconfig, QObject *parent):QObject(parent)\
,m_sev(sev),m_gConfig(gconfig)
{

}
IUiControler::~IUiControler()
{
  qDebug()<<"IUiControler-->destruct";
}
