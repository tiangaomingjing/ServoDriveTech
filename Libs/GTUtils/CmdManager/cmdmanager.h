#ifndef CMDMANAGER_H
#define CMDMANAGER_H

#include <QObject>
#include <QMap>
#include "gtutils_global.h"

class GTUTILSSHARED_EXPORT CmdManager : public QObject
{
    Q_OBJECT
public:
    explicit CmdManager(QObject *parent = 0);
    int getValue(const QString &key);
private:
    QString m_tablePath;
    QMap<QString, int> m_map;
private:
    QVariant data(const QString &group, const QString &key, const QVariant &defaultValue);
    void iniMap();
signals:

public slots:
};

#endif // CMDMANAGER_H
