#include "dbvermatching.h"
#include "../../../Libs/GTUtils/gtutils.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QSqlTableModel>
#include <QSqlRecord>

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
    QString dbPath = GTUtils::databasePath() + "Version/";
    db.setDatabaseName(dbPath + "testdatabase.db");
    db.setUserName("root");
    db.setPassword("");
    if (!db.open()) {
        qDebug()<<"Fail!";
        return false;
    }
    QFile file(dbPath + "Types.ini");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"File Open Error!";
        return false;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    m_typeList = line.split("-");
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
  //list<<"P1-C1-V1-F1";
  //增加数据库的link
    QString tableName = "Summary";
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();
    for (int i = 0; i < model->rowCount(); i++) {
        QString str = "";
        QSqlRecord record = model->record(i);
        for (int j = 0; j < m_typeList.count(); j++) {
            QString role = m_typeList.at(j);
            str = str + role + record.value(role).toString();
            if (j < m_typeList.count() - 1) {
                str = str + "-";
            }
        }
        list.append(str);
    }
    delete model;
}
bool DbVerMatching::hasComponent(const VerInfo &verinfo)
{
    QStringList verList;
    verList.append(QString::number(verinfo.c));
    verList.append(QString::number(verinfo.v));
    verList.append(QString::number(verinfo.f));
    verList.append(QString::number(verinfo.p));
    QSqlTableModel* model = new QSqlTableModel(this);
    for (int i = 0; i < m_typeList.count(); i++) {
        QString role = m_typeList.at(i);
        QString tableName = "Single" + role;
        model->setTable(tableName);
        QString filter = role + "==" + verList.at(i);
        model->setFilter(filter);
        model->select();
        if (model->rowCount() == 0) {
            delete model;
            return false;
        }
    }
    delete model;
  return true;
}


