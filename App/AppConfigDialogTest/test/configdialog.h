#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigDialog;
}
class DeviceConfig;
class QTreeWidgetItem;
class ConfigDialog : public QDialog
{
  Q_OBJECT

public:
  enum SelectStatus{
    SELECT_STATUS_PCDEBUG,
    SELECT_STATUS_RNNET
  };
  enum DstTreeStatus{
    DST_TREE_STATUS_EMPTY,
    DST_TREE_STATUS_PCDEBUG,
    DST_TREE_STATUS_RNNET
  };
  enum ConfigColumnInx{
    COL_NAME,
    COL_PRM,
    COL_ID,
    COL_PRM_EX0
  };

  explicit ConfigDialog(QList<DeviceConfig*> *devList,QWidget *parent = 0);
  ~ConfigDialog();

private slots:
  void onSrcTreeItemClicked(QTreeWidgetItem*item,int column);
  void onBtnAddClicked();
  void onBtnRemoveClicked();
  void onBtnCancelClicked();
  void onBtnApplyClicked();

private:
  QString readDeviceDescription(const QString &sdinfoPath);
  void setDevicePreview(const QString &sd);
  void loadSrcTreeWidget();
  void createConnections();
  void setCurrentUiSelectStatus(SelectStatus sta);
  void createDstDevice(QTreeWidgetItem*curItem);
  QTreeWidgetItem* addChildItem(QTreeWidgetItem*child,QTreeWidgetItem*parent);
  void resetDeviceId();

private:
  Ui::ConfigDialog *ui;
  QList<DeviceConfig*> *m_devListPtr;
  QString m_iconProductPath;
  QString m_curSd;
  SelectStatus m_curSelectSta;
  DstTreeStatus m_curDstTreeSta;


};

#endif // CONFIGDIALOG_H
