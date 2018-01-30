#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigDialog;
}
class DeviceConfig;
class ConfigDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ConfigDialog(QList<DeviceConfig*> *devList,QWidget *parent = 0);
  ~ConfigDialog();

private:
  QString readDeviceDescription(const QString &sdinfoPath);
  void setDevicePreview(const QString &sd);
  void loadSrcTreeWidget();
private:
  Ui::ConfigDialog *ui;
  QList<DeviceConfig*> *m_devListPtr;
  QString m_iconProductPath;


};

#endif // CONFIGDIALOG_H
