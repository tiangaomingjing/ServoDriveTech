#ifndef CMD_H
#define CMD_H

#include <QObject>
namespace ComDriver {
class ICom;
}
class QTreeWidget;
class QTreeWidgetItem;

class GeneralCmd:public QObject
{
  Q_OBJECT
public:
  explicit GeneralCmd(ComDriver::ICom *icom,QObject *parent=0);
  ~GeneralCmd();
  bool fillCmdMaps(QTreeWidget *cmdTree);

  quint64 read(const QString &cmdReadName,qint16 axisIndex,bool &isOk);
  qint16 readErrorCode();
  bool write(const QString &cmdWriteName,quint64 value,qint16 axisIndex);
  bool containsCmd(const QString &cmdName);

  void setICom(ComDriver::ICom *icom);

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

};

#endif // CMD_H
