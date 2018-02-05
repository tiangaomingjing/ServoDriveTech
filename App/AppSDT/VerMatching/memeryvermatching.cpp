#include "memeryvermatching.h"

MemeryVerMatching::MemeryVerMatching(QObject *parent) : IVerMatching(parent)
{

}
MemeryVerMatching::~MemeryVerMatching()
{

}

bool MemeryVerMatching::open()
{
  //打开数据库
  return true;
}

bool MemeryVerMatching::close()
{
  //关闭数据库
  return true;
}

void MemeryVerMatching::fillVerLinkLists(QStringList &list)
{
  list<<"C21000543-V130-F4307-P21000541";
  //增加数据库的link

}

bool MemeryVerMatching::hasComponent(const VerInfo &verinfo)
{
  Q_UNUSED(verinfo);
//  return false;//TEST
  return true;
}
