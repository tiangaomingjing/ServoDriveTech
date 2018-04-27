#ifndef BITITEMHELPER_H
#define BITITEMHELPER_H

#include <QObject>
#include <QMap>
#include "gtutils_global.h"
#include "icom.h"

class QTreeWidget;
class QTreeWidgetItem;

namespace ComDriver {
    class ICom;
}

class GTUTILSSHARED_EXPORT BitItemHelper : public QObject
{
    Q_OBJECT
public:
    explicit BitItemHelper(QObject *parent = 0);
    void assign16Bits(QTreeWidgetItem *item, ComDriver::uint16_t value);
    void assign32Bits(QTreeWidgetItem *item, ComDriver::uint32_t value);
    void assign64Bits(QTreeWidgetItem *item, ComDriver::uint64_t value);
    quint16 calculate16Bits(QTreeWidgetItem *item);
    quint32 calculate32Bits(QTreeWidgetItem *item);
    quint64 calculate64Bits(QTreeWidgetItem *item);
    bool isTargetItem(QTreeWidgetItem *item, const QString &str, int index);
signals:

public slots:

private:
    QString m_tablePath;
private:   
    quint64 getOperationValue(int start, int length);
};

#endif // BITITEMHELPER_H
