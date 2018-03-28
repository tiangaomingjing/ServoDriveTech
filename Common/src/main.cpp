#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <QTreeWidget>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>

#include "test.h"
#include <iostream>



template <typename T>
class ListClear
{
public:
  ListClear(){}
  ~ListClear(){}
  static void clearList(QList<T*>&list)
  {
    T* item;
    for(int i=0;i<list.count();i++)
    {
      item=list.at(i);
      delete item;
    }
    list.clear();
  }
};

template <typename T>
static void clearListTest(QList<T*>&list)
{
  T* item;
  for(int i=0;i<list.count();i++)
  {
    item=list.at(i);
    delete item;
  }
  list.clear();
}

//读回来的目录有"..","." 测试失败，所以不用这种方法
void getFileDirNameTest()
{
  QString stylepath="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/build/debug/custom/option/style/";
  QDir dir(stylepath);
  QFileInfoList fileList;
  dir.setFilter(QDir::Dirs | QDir::Hidden | QDir::NoSymLinks);
  dir.setSorting(QDir::Size | QDir::Reversed);
  fileList=dir.entryInfoList();
  QStringList slist=dir.entryList();
  qDebug()<<"s list count"<<slist.count();
  foreach (QString s, slist) {
    qDebug()<<s;
  }
  qDebug()<<"file list count"<<fileList.count();
  int i=0;
  foreach (QFileInfo fileInfo, fileList) {
    qDebug()<<"--------------------index"<<i++;
    qDebug()<<"basename"<<fileInfo.baseName();
    qDebug()<<"is dir"<<fileInfo.isDir();
    qDebug()<<"dirName"<<fileInfo.dir().dirName();
  }
}
//[TEST]
void readStyleINI()
{
  QString filename="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/build/debug/custom/option/style/style.ini";
  QFile file(filename);
  file.open(QFile::ReadOnly);
  QTextStream in(&file);
  QStringList list;
  QString s;
  while (!in.atEnd()) {
    s=in.readLine();
    qDebug()<<s;
    list.append(s);
  }
  list.removeAll("");
  qDebug()<<"after remove null"<<list;
  foreach (QString s, list) {
    if(!s.isEmpty())
      qDebug()<<s;
  }

  file.close();
}


class A
{
public:
  ~A(){}
  virtual void display(){dosomething();}
protected:
  virtual void dosomething(){}
//  void dosomething(){}//这个没有通过多态的方式调用
};
class B:public A
{
public:
  B(){}
protected:
  void dosomething()
  {
    std::cout<<"this is B";
  }
};
class C:public B
{
protected:
  void dosomething()
  {
    std::cout<<"this is C";
  }
};

int main(int argc, char *argv[])
{
//  QCoreApplication a(argc, argv);
  QApplication a(argc, argv);
//  QTreeWidget *tree;
//  tree=QtTreeManager::createTreeWidgetFromXmlFile("SysConfigTree.ui");
//  tree->show();


  QString str = "f0";
  bool ok;
  uint hex = str.toUInt(&ok, 16);
  qDebug()<<hex;

//  getFileDirNameTest();
//  readStyleINI();

  qDebug()<<"10.00 toUshort"<<QString("10.00").toUShort();
  qDebug()<<"10.00.toDouble()"<<QString("10.00").toDouble();

  B *b=new C;
  b->display();

  qDebug()<<"sizeof uint"<<sizeof(uint);
  qDebug()<<"sizeof int"<<sizeof(int);
  qDebug()<<"sizeof ushort"<<sizeof(ushort);
  qDebug()<<"sizeof uint"<<sizeof(ulong);

  return a.exec();
}

