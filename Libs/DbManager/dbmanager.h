#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QSqlTableModel>
#include "dbmanager_global.h"

class DBMANAGERSHARED_EXPORT DBManager : public QObject
{
    Q_OBJECT
public:
    DBManager(QString dbPath, QString userName, QString psw);
    bool checkRole(QString role, QString psw);
    QList<QSqlTableModel*> getRoleModels(QString role);
    bool checkValid(QStringList strList);
    QStringList readSingleTable(QString role);
    bool checkCoupleValid(QString strOne, QString strTwo, int i, int j);
    void writeSingle(QString role, QStringList strList);
    void writeRelation(QString firstRole, QString secondRole, QStringList strList);
    void writeSummary();
    void addSingle(QString role, QString str);
    void addRelation(QString firstRole, QString secondRole, QStringList strList);
    void deleteSingle(QString role, QString str);
    void deleteRelation(QString firstRole, QString secondRole, QString str);
public:
    QStringList typeList;
private:
    void getLink(QString str, int count, QString list);
    bool checkPreviousValid(QString str, int count, QString list);
    void writeSummaryTable(QString tableName, QString list);
    void clearTable(QString tableName);
    void writeTable(QSqlTableModel *model, QStringList list);
private:
    QSqlDatabase db;    
};

#endif // DBMANAGER_H
