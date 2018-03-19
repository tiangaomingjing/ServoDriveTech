#ifndef DEVICEINFODIALOG_H
#define DEVICEINFODIALOG_H

#include <QDialog>

namespace Ui {
class DeviceInfoDialog;
}

class DeviceInfoDialog : public QDialog
{
  Q_OBJECT

public:
  explicit DeviceInfoDialog(QWidget *parent = 0);
  ~DeviceInfoDialog();

private:
  Ui::DeviceInfoDialog *ui;
};

#endif // DEVICEINFODIALOG_H
