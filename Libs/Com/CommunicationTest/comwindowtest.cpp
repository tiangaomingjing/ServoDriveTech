#include "comwindowtest.h"
#include "ui_comwindowtest.h"
#include "icom.h"
#include "rnnet.h"
#include "QtTreeManager/qttreemanager.h"

#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>

ComWindowTest::ComWindowTest(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ComWindowTest)
{
  ui->setupUi(this);
  icom=new ComDriver::RnNet();
  ui->progressBar->setValue(0);
}

ComWindowTest::~ComWindowTest()
{
  delete ui;
}

void ComWindowTest::on_btn_open_clicked()
{
  ComDriver::uint16_t ret;

  ret=icom->open(processCallback,(void*)(ui->progressBar));
  qDebug()<<ret;

//  QString fileName="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/Libs/Com/CommunicationTest/FlashPrm_AllAxis.xml";
  QString fileName=QApplication::applicationDirPath()+"/FlashPrm_AllAxis.xml";
  qDebug()<<fileName;
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

//  fileName="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/Libs/Com/CommunicationTest/ret.xml";
  fileName=QApplication::applicationDirPath()+"/ret.xml";
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
        ComDriver::uint16_t ofst=itemChild->text(3).toUShort();

        if(itemChild->text(2)=="int16")
        {
          ComDriver::int16_t v;
          icom->readFLASH16(axis,ofst,0,v);

          itemChild->setText(1,QString::number(v));
        }
        else if(itemChild->text(2)=="Uint16")
        {

          ComDriver::int16_t v;
          icom->readFLASH16(axis,ofst,0,v);
          ComDriver::uint16_t n=v;

          itemChild->setText(1,QString::number(n));
        }
        else if(itemChild->text(2)=="int32")
        {
          bytesNum=4;

          ComDriver::int32_t v;
          icom->readFLASH32(axis,ofst,0,v);

          itemChild->setText(1,QString::number(v));
        }
        else if(itemChild->text(2)=="Uint32")
        {
          bytesNum=4;

          ComDriver::int32_t v;
          icom->readFLASH32(axis,ofst,0,v);
          ComDriver::uint32_t n=v;
          itemChild->setText(1,QString::number(n));
        }
        else if(itemChild->text(2)=="int64")
        {
          bytesNum=8;

          ComDriver::int64_t v;
          icom->readFLASH64(axis,ofst,0,v);

          itemChild->setText(1,QString::number(v));
        }
        else if(itemChild->text(2)=="Uint64")
        {
          bytesNum=8;

          ComDriver::int64_t v;
          icom->readFLASH64(axis,ofst,0,v);
          ComDriver::uint64_t n=v;

          itemChild->setText(1,QString::number(n));
        }
        else
        {
          bytesNum=2;

          ComDriver::int16_t v;
          icom->readFLASH16(axis,ofst,0,v);

          itemChild->setText(1,QString::number(v));
        }

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
