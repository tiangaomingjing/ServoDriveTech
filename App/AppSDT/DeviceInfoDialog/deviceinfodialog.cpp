#include "deviceinfodialog.h"
#include "ui_deviceinfodialog.h"

DeviceInfoDialog::DeviceInfoDialog(const QList<SevDevice*> &devList,QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DeviceInfoDialog),
  m_devList(devList)
{
  ui->setupUi(this);
}

DeviceInfoDialog::~DeviceInfoDialog()
{
  delete ui;
}
