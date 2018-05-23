#include "gtutils.h"
#include <QApplication>
#include <QDir>
#include <QTime>
#include <QTreeWidget>
#include <QDebug>
#include <QTranslator>

//这些路径都是相对debug/release目录下
#define DIR_COMMON "common/"
#define DIR_CUSTOM "custom/"
#define DIR_RESOURCE "resource/"
#define DIR_SYS "sysconfig/"
#define DIR_DATABASE "resource/database/"
#define DIR_ICON "resource/icon/"
#define DIR_UBOOT "resource/uboot/"
#define DIR_LANGUAGE "resource/language/"
#define DIR_CMD "resource/cmd/"


GTUtils::GTUtils()
{
}
QString GTUtils::exePath()
{
  return QApplication::applicationDirPath();
}

QString GTUtils::commonPath()
{
  QString path=sdtPath()+DIR_COMMON;
  return path;
}

QString GTUtils::customPath()
{
  QString path=sdtPath()+DIR_CUSTOM;
  return path;
}

QString GTUtils::resPath()
{
  QString path=sdtPath()+DIR_RESOURCE;
  return path;
}

QString GTUtils::sysPath()
{
  QString path=sdtPath()+DIR_SYS;
  return path;
}
QString GTUtils::databasePath()
{
  QString path=sdtPath()+DIR_DATABASE;
  return path;
}
QString GTUtils::iconPath()
{
  QString path=sdtPath()+DIR_ICON;
  return path;
}

QString GTUtils::ubootPath()
{
  QString path=sdtPath()+DIR_UBOOT;
  return path;
}

QString GTUtils::languagePath()
{
  QString path=sdtPath()+DIR_LANGUAGE;
  return path;
}

QString GTUtils::cmdPath()
{
    QString path=sdtPath()+DIR_CMD;
    return path;
}

void GTUtils::delayms(quint16 ms)
{
  QTime dieTime = QTime::currentTime().addMSecs(ms);
  while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
QList<QTranslator*> GTUtils::setupTranslators(const QString &path)
{
  QList<QTranslator*> trList;
  QStringList qmlist;
  QDir dir(path);
//  dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
//  dir.setSorting(QDir::Size | QDir::Reversed);
  QStringList nameFilters;
  nameFilters<<"*.qm";
  qmlist=dir.entryList(nameFilters,QDir::Files|QDir::Hidden|QDir::NoSymLinks,QDir::Name);
  qDebug()<<"qm count"<<qmlist.count();

  QTranslator *trans=NULL;
  foreach (QString qm, qmlist)
  {
    trans=new QTranslator;
    trList.append(trans);
    QString fileqm=path+qm;
    qDebug()<<"load"<<fileqm;
    trans->load(fileqm);
    qApp->installTranslator(trans);
  }
  return trList;
}

void GTUtils::clearTreeWidgetList(QList<QTreeWidget *> &list)
{
  QTreeWidget *tree;
  for(int i=0;i<list.count();i++)
  {
    tree=list.at(i);
    delete tree;
  }
  list.clear();
}
QTreeWidgetItem* GTUtils::findTopLevelItem(QTreeWidgetItem *item)
{
  QTreeWidgetItem* top=item;
  while(top->parent()!=NULL)
    top=top->parent();
  return top;
}


QTreeWidgetItem* GTUtils::findItem(const QString &text, QTreeWidget* tree, int col) {
    QTreeWidgetItemIterator treeIter(tree);
    QTreeWidgetItem *result = NULL;
    while (*treeIter){
        if ((*treeIter)->text(col).compare(text) == 0) {
            result = *treeIter;
            return result;
        }
        ++treeIter;
    }
    return result;
}

QTreeWidgetItem* GTUtils::findItemInItem(const QString &text, QTreeWidgetItem* treeItem, int col)
{
  QTreeWidgetItem *result = NULL;
//  qDebug()<<treeItem->text(col);
  if(treeItem->text(col).compare(text) == 0)
  {
    result = treeItem;
    return result;
  }
  else
  {
    for(int i = 0;i<treeItem->childCount();i++)
    {
      result = findItemInItem(text,treeItem->child(i),col);
      if(result != NULL)
        break;
    }
    return result;
  }

}

int GTUtils::byteNumbers(const QString &str)
{
  int num;
  if(str.contains("16"))
    num=2;
  else if(str.contains("32"))
    num=4;
  else if(str.contains("64"))
    num=8;
  else
    num=2;
  return num;
}

//--------------------private function-------------------------------
QString GTUtils::sdtPath()
{
  QString path=qApp->applicationDirPath();
  QDir dir(path);
  dir.cdUp();
  path=dir.absolutePath()+"/";
  return path;
}


