#include "treemanager.h"

#include<QFormBuilder>
#include<QTreeWidgetItem>
#include<QTreeWidget>
#include<QMessageBox>
#include<QWidget>
#include<QVBoxLayout>
#include<QXmlStreamWriter>
#include<QDebug>

TreeManager::TreeManager(QObject *parent) : QObject(parent)
{

}

//!
//! \brief QtTreeManager::createTreeWidgetFromXmlFile
//! \param fileName
//! \return QTreeWidget*:OK   NULL:error occurs
//!
QTreeWidget* TreeManager::createTreeWidgetFromXmlFile(const QString &fileName)
{
  QFormBuilder builder;
  QFile file(fileName);

  if (!file.open(QFile::ReadOnly))
  {
    QMessageBox::information(0, tr("open error"), tr("open %1 file error ").arg(fileName));
    return NULL;
  }
  QWidget *widget=NULL;
  QTreeWidget *treeWidget=NULL;

  widget = builder.load(&file, 0);
  if (widget==NULL)
  {
    QMessageBox::information(0, tr("load error"), tr("load .xml file error "));
    file.close();
    return NULL;
  }
  file.close();

  QTreeWidget *tree=widget->findChild<QTreeWidget*>("treeWidget");//可以这样子查找
  if(tree!=NULL)
  {
    treeWidget=new QTreeWidget();
    QTreeWidgetItem *item;
    for(int i=0;i<tree->topLevelItemCount();i++)
    {
      item=tree->topLevelItem(i)->clone();
      treeWidget->addTopLevelItem(item);
    }
    QTreeWidgetItem *head;
    head=tree->headerItem()->clone();
    treeWidget->setHeaderItem(head);
    delete widget;
    return treeWidget;
  }
  else
  {
    delete widget;
    QMessageBox::information(0, tr("load error"), tr("findChild treeWidget error! "));
    return NULL;
  }
}
