#include "cmdmainwindow.h"
#include "ui_cmdmainwindow.h"
#include "generalcmd.h"
#include "qttreemanager.h"

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
}
