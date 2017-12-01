#ifndef QTTREEMANAGER_H
#define QTTREEMANAGER_H

#include <QObject>
#include "gtutils_global.h"

class QTreeWidget;
class QTreeWidgetItem;
class QXmlStreamWriter;

class GTUTILSSHARED_EXPORT QtTreeManager : public QObject
{
  Q_OBJECT
public:
  explicit QtTreeManager(QObject *parent = 0);
  static QTreeWidget* createTreeWidgetFromXmlFile(const QString &fileName);
  static bool writeTreeWidgetToXmlFile(const QString &fileName, const QTreeWidget *treeWidget);
signals:

public slots:
private:
  static void writeStructXmlFile(QTreeWidgetItem *item, QXmlStreamWriter *writer);

};

#endif // QTTREEMANAGER_H
