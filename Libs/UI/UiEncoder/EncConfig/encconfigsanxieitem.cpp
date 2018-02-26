#include "encconfigsanxieitem.h"

EncConfigSanXieItem::EncConfigSanXieItem(QObject *parent):IEncConfigItem(parent)
{
  m_encConfigData=0x0003;
  setObjectName(tr("EncSanXie"));
}
EncConfigSanXieItem::~EncConfigSanXieItem()
{

}
