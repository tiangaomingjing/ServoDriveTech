#include "encconfigduomoitem.h"

EncConfigDuoMoItem::EncConfigDuoMoItem(QObject *parent) : IEncConfigItem(parent)
{
  m_encConfigData=0x0000;
  setObjectName(tr("EncDuoMoChuan"));
}
EncConfigDuoMoItem::~EncConfigDuoMoItem()
{

}

