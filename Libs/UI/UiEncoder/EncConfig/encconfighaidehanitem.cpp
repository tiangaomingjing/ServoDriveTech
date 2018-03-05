#include "encconfighaidehanitem.h"

EncConfigHaidehanItem::EncConfigHaidehanItem(QObject *parent) : IEncConfigItem(parent)
{
  m_encConfigData=0x0002;
  setObjectName(tr("EncHaidehan"));
}
EncConfigHaidehanItem::~EncConfigHaidehanItem()
{

}
