#include "cpumainwindow.h"
#include "ui_cpumainwindow.h"
#include "SystemInfo/isysinfo.h"
#include "SystemInfo/syswin.h"
#include <Windows.h>

CpuMainWindow::CpuMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::CpuMainWindow)
{
  ui->setupUi(this);
  m_sysInfo=new SysWin;
}

CpuMainWindow::~CpuMainWindow()
{
  delete ui;
}

void CpuMainWindow::on_pushButton_clicked()
{
  qDebug()<<"without sleep clicked";
  QList<QWidget *>wList;
  QWidget *w;
  for(int i=0;i<1000;i++)
  {
    w=new QWidget;
    w->show();
    wList.append(w);
  }
  qDebug()<<"release **********************";
  for(int j=0;j<wList.count();j++)
  {
    delete wList.at(j);
  }
  wList.clear();

}

void CpuMainWindow::on_pushButton_sleep_clicked()
{
  qDebug()<<"has sleep clicked";
  QList<QWidget *>wList;
  QWidget *w;
  for(int i=0;i<1000;i++)
  {
    w=new QWidget;
    w->show();
    Sleep(100);
    wList.append(w);
  }
  qDebug()<<"release **********************";
  for(int j=0;j<wList.count();j++)
  {
    delete wList.at(j);
    Sleep(100);
  }
  wList.clear();
}

void CpuMainWindow::on_pushButton_sleep_wait_clicked()
{
  qDebug()<<"has sleep  and wait clicked";
  QList<QWidget *>wList;
  QWidget *w;
  for(int i=0;i<1000;i++)
  {
    w=new QWidget;
    w->show();
    Sleep(100);
    cpuTest();//在这里有m_sysInfo->GetSysCpu(nCpuRate); WaitForSingleObject(hEvent,500);//等待500毫秒
    wList.append(w);
  }
  qDebug()<<"release **********************";
  for(int j=0;j<wList.count();j++)
  {
    delete wList.at(j);
    Sleep(100);
    cpuTest();//在这里有m_sysInfo->GetSysCpu(nCpuRate); WaitForSingleObject(hEvent,500);//等待500毫秒
  }
  wList.clear();
}
void CpuMainWindow::cpuTest()
{
  int nCpuRate = -1;
//  int nMemTotal = -1;
//  int nMemUsed = -1;
//  int nDiskTotal = -1;
//  int nDiskUsed = -1;
//  int nProcessMemRate = -1;
//  QMap<int,QString> pidMap;

  m_sysInfo->GetSysCpu(nCpuRate);
  qDebug()<<"CPU Rate:"<<nCpuRate<<"%";

//  m_sysInfo->GetSysMemory(nMemTotal,nMemUsed);
//  qDebug()<<"Mem Total:"<<nMemTotal<<"\t Mem Used:"<<nMemUsed;

//  m_sysInfo->GetSysDisk(nDiskTotal,nDiskUsed);
//  qDebug()<<"Disk Total:"<<(nDiskTotal/1024.0)<<"GB \t Disk Used:"<<(nDiskUsed/1024.0)<<"GB";

//  m_sysInfo->GetProcessMemory(6472,nProcessMemRate);
//  qDebug()<<"PID:6472;\t Mem Rate:"<<nProcessMemRate<<"%";

//  pidMap = m_sysInfo->GetAllProcess();
//  qDebug()<<"Process Number:"<<pidMap.size();

  qDebug()<<"-------------------------------------------------------------------";
}
