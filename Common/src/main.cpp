#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <QTreeWidget>

#include "qttreemanager.h"
#include "sdtglobaldef.h"
#include "gtutils.h"
#include "Kernel/globalconfig.h"
#include "Kernel/gconfigreadwriter.h"
#include "Kernel/idevreadwriter.h"
#include "Kernel/devtextrwriter.h"
#include "Kernel/deviceconfig.h"
#include "Kernel/sevdevice.h"
#include "Kernel/sevuicontroler.h"
#include "Kernel/sdassembly.h"
#include "Kernel/devcomrwriter.h"


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

int main(int argc, char *argv[])
{
//  QCoreApplication a(argc, argv);
  QApplication a(argc, argv);
  QTreeWidget *tree;
  tree=QtTreeManager::createTreeWidgetFromXmlFile("SysConfigTree.ui");
  tree->show();


  QString str = "f0";
  bool ok;

  uint hex = str.toUInt(&ok, 16);
  qDebug()<<hex;
  return a.exec();
}

