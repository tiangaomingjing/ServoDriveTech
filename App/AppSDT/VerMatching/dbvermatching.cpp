#include "dbvermatching.h"
#include "../../../Libs/GTUtils/gtutils.h"

DbVerMatching::DbVerMatching(QObject *parent) : IVerMatching(parent)
{

}
DbVerMatching::~DbVerMatching()
{

}
bool DbVerMatching::open()
{
  //打开数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = GTUtils::databasePath() + "Version/testdatabase.db";
    db.setDatabaseName(dbPath + "testdatabase.db");
    db.setUserName("root");
    db.setPassword("");
    if (!db.open()) {
        qDebug()<<"Fail!";
        return false;
    }
  return true;
}

bool DbVerMatching::close()
{
  //关闭数据库
    db.close();
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


