#include "cmdmainwindow.h"
#include "ui_cmdmainwindow.h"
#include "generalcmd.h"
#include "qttreemanager.h"
#include <QDebug>

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
  GeneralCmd::instance()->fillCmdMaps(tree);


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
