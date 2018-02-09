#ifndef CMD_H
#define CMD_H

#include "cmd_global.h"
#include <QObject>
namespace ComDriver {
class ICom;
}
class QTreeWidget;
class QTreeWidgetItem;

class CMDSHARED_EXPORT GeneralCmd:public QObject
{
  Q_OBJECT
public:
  static GeneralCmd *instance(QObject *parent=0);
  bool fillCmdMaps(QTreeWidget *cmdTree);
  double read(const QString &cmdReadName,qint16 axisIndex,bool &isOk,ComDriver::ICom *icom);
  double write(const QString &cmdWriteName,double value,qint16 axisIndex,bool &isOk,ComDriver::ICom *icom);
protected:
  GeneralCmd(QObject *parent=0);
  GeneralCmd(GeneralCmd &oc){Q_UNUSED(oc);}
private:
  void fillItemMaps(QTreeWidgetItem *item);
private:
  enum COL_CMD_FUNC_INDEX
  {
    COL_CMD_FUNC_NAME,
    COL_CMD_FUNC_TYPE,
    COL_CMD_FUNC_UNIT,
    COL_CMD_FUNC_CMD,
    COL_CMD_FUNC_LENGTH,
    COL_CMD_FUNC_SETINDEX,
    COL_CMD_FUNC_GETINDEX,
    COL_CMD_FUNC_KGAIN,
    COL_CMD_FUNC_ID
  };
  class GeneralCmdPrivateData;
  GeneralCmdPrivateData *m_dataPtr;
  static GeneralCmd* m_instance;

};

#endif // CMD_H
