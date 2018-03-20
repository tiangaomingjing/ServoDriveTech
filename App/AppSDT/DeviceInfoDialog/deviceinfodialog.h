#ifndef DEVICEINFODIALOG_H
#define DEVICEINFODIALOG_H

#include <QDialog>

namespace Ui {
class DeviceInfoDialog;
}
namespace ComDriver {
class ICom;
}
class SevDevice;
class QTreeWidgetItem;

class DeviceInfoDialog : public QDialog
{
  Q_OBJECT

public:
  explicit DeviceInfoDialog(QWidget *parent = 0);
  ~DeviceInfoDialog();

  void readInfo(const QList<SevDevice*> &devList);
private slots:
  void onBtnOkClicked();
private:
  void readCurrentDeviceInfo(SevDevice *dev, QTreeWidgetItem *parentItem, quint8 index);
  static void processCallBack(void *argv,short *value);
private:
  Ui::DeviceInfoDialog *ui;
  QList<SevDevice*>m_devList;
};

#endif // DEVICEINFODIALOG_H
