#include "encconfigsongxiaitem.h"

EncConfigSongXiaItem::EncConfigSongXiaItem(QObject *parent) : IEncConfigItem(parent)
{
  m_encConfigData=0x0004;
  setObjectName(tr("EncSongXia"));
}

EncConfigSongXiaItem::~EncConfigSongXiaItem()
{

}
