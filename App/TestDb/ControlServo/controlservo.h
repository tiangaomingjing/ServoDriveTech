#ifndef CONTROLSERVO_H
#define CONTROLSERVO_H

#include <QObject>
#include "globaldefine.h"
#include "Basetype_def.h"
#include "ServoDriverComDll.h"

class QTreeWidget;
class QTreeWidgetItem;

class ControlServo : public QObject
{
  Q_OBJECT
public:
  explicit ControlServo(QObject *parent = 0);
  ~ControlServo();
  static void writeServoFlash(QTreeWidgetItem *item, int axisIndex, COM_TYPE comtype, short comStation);
  void writeServoFlashByAxisTree(QTreeWidget *tree, int axisIndex, COM_TYPE comtype, short comStation);
  void writeServoFlashByAllAxisTree(QTreeWidget *alltree, COM_TYPE comtype, short comStation);

signals:
  void progressValue(int value);

public slots:
private:
  quint32 totalItemCount(QTreeWidget*tree);
};

#endif // CONTROLSERVO_H
