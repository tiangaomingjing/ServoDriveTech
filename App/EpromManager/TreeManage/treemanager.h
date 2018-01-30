#ifndef TREEMANAGER_H
#define TREEMANAGER_H

#include <QObject>
class QTreeWidget;
class QTreeWidgetItem;
class QXmlStreamWriter;

class TreeManager : public QObject
{
  Q_OBJECT
public:
  explicit TreeManager(QObject *parent = 0);
  static QTreeWidget* createTreeWidgetFromXmlFile(const QString &fileName);
signals:

public slots:


};

#endif // TREEMANAGER_H
