#include "cmdmainwindow.h"
#include "ui_cmdmainwindow.h"
#include "generalcmd.h"
#include "qttreemanager.h"

#include "icom.h"
#include "rnnet.h"

#include <QDebug>
#include <QTreeWidget>

CmdMainWindow::CmdMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::CmdMainWindow)
{
  ui->setupUi(this);

}

CmdMainWindow::~CmdMainWindow()
{
  delete ui;
}

void CmdMainWindow::on_pushButton_fillmaps_clicked()
{
  QString path="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/build/debug/sysconfig/SD6x/SD61/V129/cmd/GeneralCmd.xml";
  QTreeWidget *tree=QtTreeManager::createTreeWidgetFromXmlFile(path);
  m_gencmd->fillCmdMaps(tree);
  delete tree;


  qDebug()<<"=========================================";
  quint16 data[4];

  quint32 t1=131072;
  quint64 ret=0;

  for(int i=0;i<sizeof(t1)/sizeof(quint16);i++)
  {
    data[i]=t1>>16*i;
    ret+=data[i]<<(16*i);
  }
  qDebug()<<"t1="<<t1<<"ret"<<ret;

  quint32 t2=131072888;
  ret=0;
  for(int i=0;i<sizeof(t2)/sizeof(quint16);i++)
  {
    data[i]=t2>>16*i;
    ret+=data[i]<<(16*i);
  }
  qDebug()<<"t2="<<t2<<"ret"<<ret;
}

void CmdMainWindow::on_pushButton_open_clicked()
{
  int ret=-1;
  ComDriver::ICom *icom=new ComDriver::RnNet("RnNet");
  ret=icom->open(NULL,NULL);
  m_gencmd=new GeneralCmd(icom);
  qDebug()<<"open status"<<ret;

}

void CmdMainWindow::on_pushButton_16Read_clicked()
{
  bool isOk;
  quint16 value=m_gencmd->read(ui->lineEdit_16r->text(),0,isOk);
  qDebug()<<"16 read "<<isOk<<ui->lineEdit_16r->text()<<value<<"  int16"<<(qint16)value;
}

void CmdMainWindow::on_pushButton_32Read_clicked()
{
  bool isOk;
  quint32 value=m_gencmd->read(ui->lineEdit_32r->text(),0,isOk);
  qDebug()<<"32 read uint32"<<isOk<<ui->lineEdit_32r->text()<<value<<"   int32"<<(qint32)value;
}

void CmdMainWindow::on_pushButton_16Write_clicked()
{
  quint16 value=ui->doubleSpinBox_16w->value();
  bool isOk=false;
  isOk=m_gencmd->write(ui->lineEdit_16w->text(),value,0);
  quint16 value2=m_gencmd->read(ui->lineEdit_16w->text(),0,isOk);
  qDebug()<<ui->lineEdit_16w->text()<<tr("uint16 write %1, read %2").arg(value).arg(value2)<<tr("  int16 write %1, read %2").arg((qint32)value).arg((qint32)value2);
}

void CmdMainWindow::on_pushButton_32Write_clicked()
{
  quint32 value=ui->doubleSpinBox_32w->value();
  bool isOk=false;
  isOk=m_gencmd->write(ui->lineEdit_32w->text(),value,0);

  quint32 value2=m_gencmd->read(ui->lineEdit_32w->text(),0,isOk);
  qDebug()<<ui->lineEdit_32w->text()<<tr("uint32 write %1, read %2").arg(value).arg(value2)<<tr("  int32 write %1, read %2").arg((qint32)value).arg((qint32)value2);
}
