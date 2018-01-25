#include "configdialog.h"
#include "ui_configdialog.h"
#include "deviceconfig.h"
#include "gtutils.h"
#include "qttreemanager.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

#define CONFIG_SELECT_FILE_PATH "SysMap/ConfigSelectTree.ui"


ConfigDialog::ConfigDialog(QList<DeviceConfig *> *devList, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ConfigDialog),
  m_devListPtr(devList)
{
  ui->setupUi(this);

  m_iconProductPath=GTUtils::iconPath()+"product/";
  QString sd="SD61";

  setDevicePreview(sd);

  loadSrcTreeWidget();

}

ConfigDialog::~ConfigDialog()
{
  delete ui;
  qDebug()<<"ConfigDialog destruct-->";
}

QString ConfigDialog::readDeviceDescription(const QString &sdinfoPath)
{
  QFile file(sdinfoPath);
  QString sdInfo;
  if(file.open(QFile::ReadOnly|QFile::Text))
  {
    QTextStream in(&file);
    in.setCodec("UTF-8");//解决读中文时乱码
    sdInfo=in.readAll();
  }
  file.close();
  return sdInfo;
}
void ConfigDialog::setDevicePreview(const QString &sd)
{
  ui->tbtn_deviceImg->setIconSize(ui->tbtn_deviceImg->size());

  QString sd61IconPath=m_iconProductPath+sd+".png";
  ui->tbtn_deviceImg->setIcon(QIcon(sd61IconPath));

  QString sdInfoPath=m_iconProductPath+sd+".txt";
  QString sdInfo=readDeviceDescription(sdInfoPath);
  ui->label_deviceInfo->setText(sdInfo);
}
//!
//! \brief ConfigDialog::loadSrcTreeWidget
//! 注意这里加载进来的树是没有Device这个头的，为了与custom初始化的树一致，在选择到目标后要增加Device头
//!
void ConfigDialog::loadSrcTreeWidget()
{
  QString selectTreePath=GTUtils::sysPath()+CONFIG_SELECT_FILE_PATH;
  QTreeWidget *tree=QtTreeManager::createTreeWidgetFromXmlFile(selectTreePath);
  QTreeWidgetItem *item;
  for(int i=0;i<tree->topLevelItemCount();i++)
  {
    item=tree->topLevelItem(i)->clone();
    ui->treeWidget_src->addTopLevelItem(item);
  }
  ui->treeWidget_src->expandAll();
  delete tree;
}
