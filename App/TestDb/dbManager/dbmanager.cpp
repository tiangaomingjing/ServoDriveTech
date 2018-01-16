#include "dbmanager.h"
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>

DBManager::DBManager(QString dbPath, QString userName, QString psw)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath + "testdatabase.db");
    db.setUserName(userName);
    db.setPassword(psw);
    if (!db.open()) {
        qDebug()<<"Fail!";
        return;
    }
    QFile file(dbPath + "Types.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"File Open Error!";
        return;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    typeList = line.split("-");
}

bool DBManager::checkRole(QString role, QString psw) {
    QSqlTableModel model;
    model.setTable("UserInformation");
    QString filter = QString("UserRole = '%1'").arg(role);
    model.setFilter(filter);
    model.select();
    QSqlRecord record = model.record(0);
    QString pswStr = record.value("Password").toString();
    if (pswStr.compare(psw) == 0) {
        return true;
    }
    return false;
}

QList<QSqlTableModel*> DBManager::getRoleModels(QString role) {
    QList<QSqlTableModel*> results;
    QStringList tableList = db.tables();
    for (int i = 0; i < tableList.count(); i++) {
        QString tableStr = tableList.at(i);
        if (tableStr.left(8).compare("Relation") == 0 && tableStr.right(2).contains(role, Qt::CaseInsensitive)) {
            QSqlTableModel *model = new QSqlTableModel(this);
            QString firstID = tableStr.at(8);
            QString secondID = tableStr.at(9);
            model->setTable(tableStr);
            model->setHeaderData(0, Qt::Horizontal, firstID);
            model->setHeaderData(1, Qt::Horizontal, secondID);
            model->select();
            results.append(model);
            //delete model;
        }
    }
    return results;
}

bool DBManager::checkValid(QStringList strList) {
    for (int i = 0; i < strList.count(); i++) {
        QString strOne = strList.at(i);
        for (int j = i + 1; j < strList.count(); j++) {
            QString strTwo = strList.at(j);
            if (!checkCoupleValid(strOne, strTwo, i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool DBManager::checkCoupleValid(QString strOne, QString strTwo, int i, int j) {
    if (i == j) {
        return false;
    }
    if (i > j) {
        QString str = strOne;
        strOne = strTwo;
        strTwo = str;
        int k = i;
        i = j;
        j = k;
    }
    QString tableName = "Relation" + typeList.at(i) + typeList.at(j);
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();
    for (int k = 0; k < model->rowCount(); k++) {
        QSqlRecord record = model->record(k);
        QString firstStr = record.value(typeList.at(i)).toString();
        if (firstStr.compare(strOne) == 0) {
            QString secondStr = record.value(typeList.at(j)).toString();
            if (secondStr.compare(strTwo) == 0) {
                delete model;
                return true;
            }
        }
    }
    delete model;
    return false;
}

void DBManager::writeSummary() {
    clearTable("Summary");
    QString tableName = "Relation" + typeList.at(0) + typeList.at(1);
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();
    for (int i = 0; i < model->rowCount(); i++) {
        QSqlRecord record = model->record(i);
        QString strOne = record.value(typeList.at(0)).toString();
        QString strTwo = record.value(typeList.at(1)).toString();
        QString list = strOne + "-" + strTwo;
//        qDebug()<<list;
        getLink(strTwo, 1, list);
    }
    delete model;
}

void DBManager::getLink(QString str, int count, QString list) {
    if (count < typeList.count() - 1) {
        QString tableName = "Relation" + typeList.at(count) + typeList.at(count + 1);
        QSqlTableModel* model = new QSqlTableModel(this);
        model->setTable(tableName);
        model->select();
        for (int i = 0; i < model->rowCount(); i++) {
            QSqlRecord record = model->record(i);
            QString strOne = record.value(typeList.at(count)).toString();
            if (strOne.compare(str) == 0) {
                QString strTwo = record.value(typeList.at(count + 1)).toString();
                if (checkPreviousValid(strTwo, count + 1, list)) {
                    getLink(strTwo, count + 1, list + "-" + strTwo);
                }
            }
        }
        delete model;
    } else {
        writeSummaryTable("Summary", list);
    }
}

bool DBManager::checkPreviousValid(QString str, int count, QString list) {
    QStringList strList = list.split("-");
    if (count - 2 >= 0) {
        for (int i = 0; i <= count - 2; i++) {
            if (!checkCoupleValid(strList.at(i), str, i, count)) {
                return false;
            }
        }
    }
    return true;
}

void DBManager::writeSummaryTable(QString tableName, QString list) {
    //qDebug()<<"ss";
    QStringList strList = list.split("-");
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable(tableName);
    int row = model->rowCount();
    model->insertRow(row);
    for (int i = 0; i < strList.count(); i++) {
        model->setData(model->index(row, i), strList.at(i));
    }
    model->submitAll();
    delete model;
}

QStringList DBManager::readSingleTable(QString role) {
    QStringList result;
    QString tableName = "Single" + role;
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();
    for (int i = 0; i < model->rowCount(); i++) {
        QSqlRecord record = model->record(i);
        QString str = record.value(role).toString();
        result.append(str);
    }
    delete model;
    return result;
}

void DBManager::clearTable(QString tableName) {
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();
    for (int i = 0; i < model->rowCount(); i++) {
        model->removeRow(i);
    }
    model->submitAll();
    delete model;
}

void DBManager::writeSingle(QString role, QStringList strList) {
    QString tableName = "Single" + role;
    clearTable(tableName);
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();
    writeTable(model, strList);
    delete model;
}

void DBManager::writeRelation(QString firstRole, QString secondRole, QStringList strList) {
    QString tableName;
    int firstIndex = typeList.indexOf(firstRole);
    int secondIndex = typeList.indexOf(secondRole);
    if (firstIndex == -1 || secondIndex == -1 || firstIndex == secondIndex) {
        return;
    } else if (firstIndex < secondIndex) {
        tableName = "Relation" + firstRole + secondRole;
    } else {
        tableName = "Relation" + secondRole + firstRole;
    }
    clearTable(tableName);
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();
    writeTable(model, strList);
    delete model;
}

void DBManager::writeTable(QSqlTableModel *model, QStringList list) {
    for (int i = 0; i < list.count(); i++) {
        QString tempStr = list.at(i);
        QStringList tempList = tempStr.split("-");
        int row = model->rowCount();
        model->insertRow(row);
        for (int j = 0; j < tempList.count(); j++) {
            model->setData(model->index(row, j), tempList.at(j));
        }
        model->submitAll();
    }
    //model->submitAll();
}

void DBManager::addSingle(QString role, QString str) {
    QString tableName = "Single" + role;
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();
    int row = model->rowCount();
    model->insertRow(row);
    model->setData(model->index(row, 0), str);
    model->submitAll();
    delete model;
}

void DBManager::addRelation(QString firstRole, QString secondRole, QStringList strList) {
    QString tableName;
    int firstIndex = typeList.indexOf(firstRole);
    int secondIndex = typeList.indexOf(secondRole);
    if (firstIndex == -1 || secondIndex == -1 || firstIndex == secondIndex) {
        return;
    } else if (firstIndex < secondIndex) {
        tableName = "Relation" + firstRole + secondRole;
    } else {
        tableName = "Relation" + secondRole + firstRole;
    }
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();
    writeTable(model, strList);
    delete model;
}

void DBManager::deleteSingle(QString role, QString str) {
    QString tableName = "Single" + role;
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();
    for (int i = 0; i < model->rowCount(); i++) {
        QSqlRecord record = model->record(i);
        QString strOne = record.value(role).toString();
        if (strOne.compare(str) == 0) {
            model->removeRow(i);
            break;
        }
    }
    model->submitAll();
    delete model;
}

void DBManager::deleteRelation(QString firstRole, QString secondRole, QString str) {
    QString tableName;
    int firstIndex = typeList.indexOf(firstRole);
    int secondIndex = typeList.indexOf(secondRole);
    if (firstIndex == -1 || secondIndex == -1 || firstIndex == secondIndex) {
        return;
    } else if (firstIndex < secondIndex) {
        tableName = "Relation" + firstRole + secondRole;
    } else {
        tableName = "Relation" + secondRole + firstRole;
    }
    QSqlTableModel* model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();
    for (int i = 0; i < model->rowCount(); i++) {
        QSqlRecord record = model->record(i);
        QString strOne = record.value(firstRole).toString();
        QString strTwo = record.value(secondRole).toString();
        QStringList strList = str.split("-");
        if (strOne.compare(strList.at(0)) == 0 && strTwo.compare(strList.at(1)) == 0) {
            model->removeRow(i);
            break;
        }
    }
    model->submitAll();
    delete model;
}
