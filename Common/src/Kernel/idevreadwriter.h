#ifndef IDEVREADWRITER_H
#define IDEVREADWRITER_H

#include <QObject>
#include "sdtglobaldef.h"
class QTreeWidget;

GT_USE_NAMESPACE
namespace ComDriver {
  class ICom;
}

class IDevReadWriter:public QObject
{
  Q_OBJECT
public:
  explicit IDevReadWriter(QTreeWidget *idMapTree,QObject *parent=0):QObject(parent),m_idMapTree(idMapTree){}
  virtual ~IDevReadWriter(){}
  virtual DeviceConfig readConfig(ComDriver::ICom *icom,bool &isOk)=0;
  virtual bool writeConfig(const DeviceConfig &config)=0;
protected:
  QTreeWidget *m_idMapTree;
};

#endif // IDEVREADWRITER_H
