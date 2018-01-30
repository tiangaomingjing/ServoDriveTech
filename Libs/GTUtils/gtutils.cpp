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

//QTreeWidgetItem* findItem(QString text, QTreeWidget* tree, int col) {
//    QTreeWidgetItemIterator treeIter(tree);
//    QTreeWidgetItem *result = NULL;
//    while (*treeIter){
//        if ((*treeIter)->text(col).compare(text) == 0) {
//            result = *treeIter;
//            return result;
//        }
//        ++treeIter;
//    }
//    return result;
//}

//QTreeWidgetItem* findItemByValue(Uint8* value, Uint16 num, QTreeWidget *tree) {
//    int tempValue = 0;
//    for (int i = 0; i < num; i++) {
//        tempValue = tempValue + (value[i] << (i * 8));
//    }
//    QTreeWidgetItemIterator treeIter(tree);
//    QTreeWidgetItem *result = NULL;
//    while (*treeIter){
//        if ((*treeIter)->text(TREE_VALUE) == QString::number(tempValue, 10)) {
//            result = *treeIter;
//            return result;
//        }
//        ++treeIter;
//    }
//    return result;
//}

//QString getPath(QTreeWidgetItem *item) {
//    QString result = item->text(TREE_NAME);
//    QString fileName = item->text(TREE_NAME) + ".ui";
//    int count = 0;
//    QTreeWidgetItem *currentItem = item;
//    while (count < 3) {
//        currentItem = currentItem->parent();
//        result = currentItem->text(TREE_NAME) + "/" + result;
//        count++;
//    }
//    result = result + "/" + fileName;
//    return result;
//}

//--------------------private function-------------------------------
QString GTUtils::sdtPath()
{
  QString path=QApplication::applicationDirPath();
  QDir dir(path);
  dir.cdUp();
  path=dir.absolutePath()+"/";
  return path;
}


