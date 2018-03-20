#include "deviceinfodialog.h"
#include "ui_deviceinfodialog.h"

#include "sevdevice.h"
#include "icom.h"
#include "deviceidhelper.h"
#include "gtutils.h"

#include <QDebug>

#define MINOR_VERSION_CONTROL_KEY "gSevDrv.no.prm.soft_min_version"

DeviceInfoDialog::DeviceInfoDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DeviceInfoDialog)
{
  ui->setupUi(this);
  QStringList list;
  list<<tr("Name")<<tr("Value");
  ui->treeWidget->setHeaderLabels(list);
  ui->treeWidget->setColumnCount(2);
  ui->treeWidget->expandAll();
  ui->treeWidget->resizeColumnToContents(0);
  connect(ui->btn_OK,SIGNAL(clicked(bool)),this,SLOT(onBtnOkClicked()));
}

DeviceInfoDialog::~DeviceInfoDialog()
{
  delete ui;
  qDebug()<<"DeviceInfoDialog destruct-->";
}

void DeviceInfoDialog::readInfo(const QList<SevDevice *> &devList)
{
  ui->treeWidget->clear();
  ui->progressBar->setValue(0);
  ui->progressBar->setVisible(true);
  int index=0;
  foreach (SevDevice *dev, devList) {
    //当前软件的节点
    qDebug()<<dev->deviceConfig()->m_version;
    QTreeWidgetItem *configItem=new QTreeWidgetItem(ui->treeWidget);
    configItem->setText(0,tr("Config Information %1").arg(1+index++));

    QTreeWidgetItem *sdtItem=new QTreeWidgetItem(configItem);
    sdtItem->setText(0,tr("SDT Information"));

    QTreeWidgetItem *modelItem=new QTreeWidgetItem(sdtItem);
    modelItem->setText(0,tr("Model"));
    modelItem->setText(1,dev->deviceConfig()->m_modeName);

    QTreeWidgetItem *verItem=new QTreeWidgetItem(sdtItem);
    verItem->setText(0,tr("Version"));
    verItem->setText(1,dev->deviceConfig()->m_version);

    QTreeWidgetItem *axisItem=new QTreeWidgetItem(sdtItem);
    axisItem->setText(0,tr("AxisNum"));
    axisItem->setText(1,QString::number(dev->deviceConfig()->m_axisNum));

    QTreeWidgetItem *comItem=new QTreeWidgetItem(sdtItem);
    comItem->setText(0,tr("ComType"));
    comItem->setText(1,QString::fromStdString(dev->socketCom()->iComObjectName()));

    ui->treeWidget->expandAll();
    GTUtils::delayms(10);
    //读实际的节点
    //如果能找到Com就显示相关信息
    if(dev->isConnecting())
    {
      //查信息
      readCurrentDeviceInfo(dev,configItem,index);
    }
    else
    {
      bool findCom=true;
      findCom=dev->adjustSocket(processCallBack,(void *)ui->progressBar);
      if(findCom)
      {
        dev->enableConnection(processCallBack,(void *)ui->progressBar);
        readCurrentDeviceInfo(dev,configItem,index);
        dev->disableConnection();
      }
    }

  }

  ui->treeWidget->expandAll();
  ui->treeWidget->resizeColumnToContents(0);
  ui->progressBar->setVisible(false);
}

void DeviceInfoDialog::onBtnOkClicked()
{
  accept();
}

void DeviceInfoDialog::readCurrentDeviceInfo(SevDevice *dev, QTreeWidgetItem *parentItem, quint8 index)
{
  DeviceIdHelper idHelper(dev->socketCom());
  quint32 dspMinVer=0xFFFFFFFF;
  quint32 fpgaVer=0xFFFFFFFF;
  quint16 year=0xFFFF;
  quint16 day=0xFFFF;
  QString sdspInfo="V???";
  QString sFpgaVer="???";
  QString sYearDay="???";

  bool ok=true;
  sdspInfo=idHelper.readVersion(ok);
  dspMinVer=dev->genCmdRead(MINOR_VERSION_CONTROL_KEY,0,ok);
  if(ok)
  {
    sdspInfo.append(QString("-%1").arg(dspMinVer));
  }
  else
  {
    sdspInfo.append(QString("-??"));
  }

  fpgaVer=idHelper.readFpgaId(ok);
  if(ok)
    sFpgaVer=QString::asprintf("%#04X",fpgaVer);

  ok=idHelper.readFpgaDate(year,day);
  if(ok)
    sYearDay=QString("%1-%2").arg(QString::asprintf("%04X",year)).arg(QString::asprintf("%04X",day));



  QTreeWidgetItem *deviceItem=new QTreeWidgetItem(parentItem);
  deviceItem->setText(0,tr("Device Information %1").arg(index));

  QTreeWidgetItem *softItem=new QTreeWidgetItem(deviceItem);
  softItem->setText(0,tr("SoftVersion"));
  softItem->setText(1,sdspInfo);

  QTreeWidgetItem *firmwareVerItem=new QTreeWidgetItem(deviceItem);
  firmwareVerItem->setText(0,tr("FirmwareVersion"));
  firmwareVerItem->setText(1,sFpgaVer);

  QTreeWidgetItem *firmwareDateItem=new QTreeWidgetItem(deviceItem);
  firmwareDateItem->setText(0,tr("FirmwareDate"));
  firmwareDateItem->setText(1,sYearDay);
}

void DeviceInfoDialog::processCallBack(void *argv, short *value)
{
  QProgressBar *pBar=static_cast<QProgressBar *>(argv);
  pBar->setValue(*value);
  qDebug()<<"progress value ="<<*value;
}
