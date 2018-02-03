#include "dbvermatching.h"

DbVerMatching::DbVerMatching(QObject *parent) : IVerMatching(parent)
{

}
DbVerMatching::~DbVerMatching()
{

}
bool DbVerMatching::open()
{
  //打开数据库
  return true;
}

bool DbVerMatching::close()
{
  //关闭数据库
  return true;
}

void DbVerMatching::fillVerLinkLists(QStringList &list)
{
  list<<"P1-C1-V1-F1";
  //增加数据库的link
}
bool DbVerMatching::hasComponent(const VerInfo &verinfo)
{
  return true;
}


