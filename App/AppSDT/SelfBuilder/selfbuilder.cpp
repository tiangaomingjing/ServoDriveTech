#include "selfbuilder.h"
#include "gtutils.h"
#include "qttreemanager.h"

#include <QFile>
#include <QTextStream>
#include <QTreeWidget>
#include <QDebug>

SelfBuilder::SelfBuilder()
{

}

void SelfBuilder::initParameters()
{
    // read axisNum, product type, series num from hardware
}

void SelfBuilder::buildNewPower(const QString &pwrID)
{
    m_typeName = "SD" + QString::number(m_axisNum) +"x";
    QString filePath = GTUtils::databasePath() + "Board/PB/newIndex_power.ini";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        QTextStream in(&file);
        QString str;
        str = in.readLine();
        int num = str.toInt();
        num++;
        QString newStr = QString::number(num);
        QTextStream out(&file);
        out<<newStr<<endl;
        m_modeName = m_typeName + "_New" + str;
    } else {
        qDebug()<<"open file error";
        return;
    }
    QString xmlPath = GTUtils::databasePath() + "Board/PB/IdMap_Power.ui";
    QTreeWidget *powerMap = QtTreeManager::createTreeWidgetFromXmlFile(xmlPath);
    QStringList nameList;
    nameList<<pwrID<<m_typeName<<m_modeName<<"nick"<<QString::number(m_axisNum);
    powerMap->addTopLevelItem(new QTreeWidgetItem(nameList));
}

void SelfBuilder::buildNewControl(const QString &ctrID)
{

}

