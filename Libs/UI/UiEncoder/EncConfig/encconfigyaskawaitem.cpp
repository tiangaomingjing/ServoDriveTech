#include "encconfigyaskawaitem.h"

EncConfigYaskawaItem::EncConfigYaskawaItem(QObject *parent) : IEncConfigItem(parent)
{
  m_encConfigData=0x0005;
  setObjectName(tr("EncYaskawa"));
}
EncConfigYaskawaItem::~EncConfigYaskawaItem()
{

}
