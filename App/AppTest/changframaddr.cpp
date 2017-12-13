#include "changframaddr.h"
#include "qttreemanager.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFileInfo>

#define COL_FRAM_ADDR 7

ChangFramAddr::ChangFramAddr(QObject *parent) : QObject(parent)
{

}

void ChangFramAddr::changeTreeAddr(const QString &fileName,int ofst)
{
  QTreeWidget *tree=QtTreeManager::createTreeWidgetFromXmlFile(fileName);
  QTreeWidgetItem  *item;
  quint16 orgAddr=0;
  for(int i=0;i<tree->topLevelItemCount();i++)
  {
    item=tree->topLevelItem(i);
    orgAddr=item->text(COL_FRAM_ADDR).toUShort();
    quint16 tarAddr=orgAddr+ofst;
    item->setText(COL_FRAM_ADDR,QString::number(tarAddr));
  }

  QString saveFilePath;
  QFileInfo fileInfo;
  fileInfo.setFile(fileName);
  saveFilePath=fileInfo.path()+"/"+fileInfo.baseName()+"1.xml";

  QtTreeManager::writeTreeWidgetToXmlFile(saveFilePath,tree);
  delete tree;
}
