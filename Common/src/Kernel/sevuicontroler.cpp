#include "sevuicontroler.h"

#include <QDebug>

SevUiControler::SevUiControler(SevDevice *sev, GlobalConfig *gconfig, QObject *parent):IUiControler(sev,gconfig,parent)
{

}
SevUiControler::~SevUiControler()
{
  qDebug()<<"SevUiControler-->destruct";
}
