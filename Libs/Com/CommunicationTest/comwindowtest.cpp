#include "comwindowtest.h"
#include "ui_comwindowtest.h"
#include "icom.h"
#include "rnnet.h"
#include "../../../Common/QtTreeManager/qttreemanager.h"

#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>

ComWindowTest::ComWindowTest(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ComWindowTest)
{
  ui->setupUi(this);
  ui->progressBar->setValue(0);
}

ComWindowTest::~ComWindowTest()
{
  delete ui;
}

void ComWindowTest::on_btn_open_clicked()
{
  ComDriver::uint16_t ret;
  icom=new ComDriver::RnNet();
  ret=icom->open(processCallback,(void*)(ui->progressBar));
  qDebug()<<ret;

  QString fileName="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/Libs/Com/CommunicationTest/FlashPrm_AllAxis.xml";

  QTreeWidget *tree=QtTreeManager::createTreeWidgetFromXmlFile(fileName);
  tree->expandAll();
  tree->resizeColumnToContents(0);
  tree->resizeColumnToContents(1);
  tree->resizeColumnToContents(2);
  tree->showMaximized();
  QTreeWidgetItem *item;
  QTreeWidgetItem *top;
  top=tree->takeTopLevelItem(0);
  for(int i=0;i<tree->topLevelItemCount();i++)
  {
    item=tree->topLevelItem(i);
    write(item,i);
  }
  tree->insertTopLevelItem(0,top);

  fileName="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/Libs/Com/CommunicationTest/ret.xml";
  QtTreeManager::writeTreeWidgetToXmlFile(fileName,tree);
}

void ComWindowTest::on_btn_test_clicked()
{
  icom->close();
  ui->progressBar->setValue(0);
}

void ComWindowTest::processCallback(void *argv, short *value)
{
  QProgressBar *bar=static_cast<QProgressBar *>(argv);
  bar->setValue(*value);
  qApp->processEvents();
  qDebug()<<"value="<<*value;
}

void ComWindowTest::write(QTreeWidgetItem *parent,int axis)
{
  static long count=0;
  for(int i=0;i<parent->childCount();i++)
  {
    QTreeWidgetItem *itemChild=parent->child(i);
    if(itemChild->childCount()==0)
    {
      //开始读操作
      if(itemChild->text(3)!="-1")
      {
        int bytesNum=2;
        ComDriver::uint64_t value;
        ComDriver::uint16_t ofst=itemChild->text(3).toUShort();

        if(itemChild->text(2)=="int16")
        {

          icom->readFLASH(axis,ofst,0,value,bytesNum);
          ComDriver::int16_t v=value;
          itemChild->setText(1,QString::number(v));
        }
        else if(itemChild->text(2)=="Uint16")
        {

          icom->readFLASH(axis,ofst,0,value,bytesNum);
          ComDriver::uint16_t v=value;
          itemChild->setText(1,QString::number(v));
        }
        else if(itemChild->text(2)=="int32")
        {
          bytesNum=4;

          icom->readFLASH(axis,ofst,0,value,bytesNum);
          ComDriver::int32_t v=value;
          itemChild->setText(1,QString::number(v));
        }
        else if(itemChild->text(2)=="Uint32")
        {
          bytesNum=4;

          icom->readFLASH(axis,ofst,0,value,bytesNum);
          ComDriver::uint32_t v=value;
          itemChild->setText(1,QString::number(v));
        }
        else if(itemChild->text(2)=="int64")
        {
          bytesNum=8;

          icom->readFLASH(axis,ofst,0,value,bytesNum);
          ComDriver::int64_t v=value;
          itemChild->setText(1,QString::number(v));
        }
        else if(itemChild->text(2)=="Uint64")
        {
          bytesNum=8;

          icom->readFLASH(axis,ofst,0,value,bytesNum);
          ComDriver::uint64_t v=value;
          itemChild->setText(1,QString::number(v));
        }
        else
        {
          bytesNum=2;

          icom->readFLASH(axis,ofst,0,value,bytesNum);
          ComDriver::int16_t v=value;
          itemChild->setText(1,QString::number(v));
        }
//        icom->readFLASH(axis,ofst,0,value,bytesNum);
//        itemChild->setText(1,QString::number(value));

        itemChild->setBackgroundColor(1,QColor(Qt::red));
      }
      count++;
      if(count%50==0)
      {
        qApp->processEvents();
      }
//      qDebug()<<" name "<<itemChild->text(0)<<" type "<<itemChild->text(2)<<" ofst "<<itemChild->text(3);
    }
    else
    {
      write(itemChild,axis);
    }
  }
}
