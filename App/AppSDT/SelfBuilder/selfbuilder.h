#ifndef SELFBUILDER_H
#define SELFBUILDER_H

#include <QObject>

class SelfBuilder
{
public:
    SelfBuilder();
private:
    QString m_modeName;
    QString m_typeName;
    int m_axisNum;
    QString m_product;
    QString m_series;
    QString m_powerID;
    QString m_controlID;
    QString m_version;
private:
    void initParameters();
    void buildNewPower(const QString &pwrID);
    void buildNewControl(const QString &ctrID);
    void buildNewVersion(const QString &version);
};

#endif // SELFBUILDER_H
