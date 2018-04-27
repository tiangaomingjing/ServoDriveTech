#include "devtextrwriter.h"
#include "Kernel/deviceconfig.h"
#include "pcdebug.h"
#include "rnnet.h"
#include "qttreemanager.h"
#include "gtutils.h"
#include "sdtglobaldef.h"

#include <QTreeWidget>

DevTextRWriter::DevTextRWriter(QObject *parent):IDevReadWriter(parent)
{

}

QList<DeviceConfig *>DevTextRWriter::createConfig(void (*processCallback)(void *pbar,short *value),void *processbar,bool &isOk)
{
  short pvalue=10;
  QList<DeviceConfig *> list;
  QString fileName=GTUtils::customPath()+DEVCONFIG_NAME;
  QTreeWidget *configTree=QtTreeManager::createTreeWidgetFromXmlFile(fileName);
  QTreeWidgetItem *devItem;
  QTreeWidgetItem *comItem;
  QTreeWidgetItem *typeItem;
  QTreeWidgetItem *modelItem;
  QTreeWidgetItem *versionItem;
  processCallback(processbar,&pvalue);

  if(configTree!=NULL)//能成功读取的
  {
    for(int i=0;i<configTree->topLevelItemCount();i++)
    {
      devItem=configTree->topLevelItem(i);
      comItem=devItem->child(0);
      typeItem=comItem->child(0);
      modelItem=typeItem->child(0);
      versionItem=modelItem->child(0);
      DeviceConfig *device=new DeviceConfig();
      device->m_devId=devItem->text(GT::COL_CONFIG_ID).toUInt();
      device->m_comType=comItem->text(GT::COL_CONFIG_PARAMETER).toUInt();
      device->m_rnStationId=comItem->text(GT::COL_CONFIG_PRMEX).toUInt();
      device->m_typeName=typeItem->text(GT::COL_CONFIG_NAME);
      device->m_axisNum=modelItem->text(GT::COL_CONFIG_PARAMETER).toUInt();
      device->m_modeName=modelItem->text(GT::COL_CONFIG_NAME);
      device->m_version=versionItem->text(GT::COL_CONFIG_NAME);

      //根据modeName typeName找到powerId
      device->m_pwrId=modelItem->text(GT::COL_CONFIG_ID).toUInt();
      device->m_ctrId=versionItem->text(GT::COL_CONFIG_ID).toUInt();
      device->m_fpgaId=comItem->text(GT::COL_CONFIG_ID).toUInt();
      list.append(device);
      pvalue+=40;
      processCallback(processbar,&pvalue);
    }
  }
  else//不成功读取的加载系统默认配置
  {
    DeviceConfig *device=new DeviceConfig();
    device->m_devId=0;
    device->m_comType=1;
    device->m_axisNum=6;
    device->m_typeName="SD6x";
    device->m_modeName="SD61_PLUS";
    device->m_version="V129";
    //根据modeName typeName找到powerId
    device->m_pwrId=2100054;
    device->m_ctrId=0;
    device->m_fpgaId=0;
    list.append(device);
  }
  pvalue=100;
  processCallback(processbar,&pvalue);

  isOk=true;

  delete configTree;

  return list;
}

bool DevTextRWriter::saveConfig(const DeviceConfig *config)
{
  return true;
}
