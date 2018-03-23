#include "sdtmainwindow.h"
#include "combinedwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

#include "optautoload.h"
#include "iopt.h"
#include "optcontainer.h"
#include "optface.h"
#include "optplot.h"
#include "optuser.h"
#include "optpath.h"

#include "gtutils.h"

#include "registerfunction.h"

#include "screenstartup.h"

#include <QDir>

#define START_UP_PIXMAP "startup.png"

//void setupTranslators(const QString &langPath )
//{
//  QStringList qmlist;
//  QDir dir(langPath);
////  dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
////  dir.setSorting(QDir::Size | QDir::Reversed);
//  QStringList nameFilters;
//  nameFilters<<"*.qm";
//  qmlist=dir.entryList(nameFilters,QDir::Files|QDir::Hidden|QDir::NoSymLinks,QDir::Name);
//  qDebug()<<"qm count"<<qmlist.count();

//  QTranslator *trans=NULL;
//  foreach (QString qm, qmlist)
//  {
//    trans=new QTranslator;
//    QString fileqm=langPath+qm;
//    qDebug()<<"load"<<fileqm;
//    trans->load(fileqm);
//    qApp->installTranslator(trans);
//  }
//}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  OptContainer *optc=OptContainer::instance();

  IOpt *opt=new OptUser("optuser",0);
  optc->addOptItem(opt);
  opt=new OptAutoLoad("optautoload",0);
  optc->addOptItem(opt);
  opt=new OptPlot("optplot",0);
  optc->addOptItem(opt);
  opt=new OptFace("optface",0);
  optc->addOptItem(opt);
  opt = new OptPath("optpath", 0);
  optc->addOptItem(opt);

  opt=optc->optItem("optface");
  OptFace *optFace=dynamic_cast<OptFace *>(opt);
  QString pixPath=GTUtils::customPath()+"option/style/"+optFace->css()+"/icon/"+START_UP_PIXMAP;
  qDebug()<<"pixPath"<<pixPath;
  ScreenStartup *startup=new ScreenStartup(QPixmap(pixPath));

  QString langPath=GTUtils::languagePath();
  QString lang;
  if(optFace->language()=="chinese")
    lang=langPath+"ch/";
  else
    lang=langPath+"en/";
  GTUtils::setupTranslators(lang);

  optFace->setFaceStyle(optFace->css());
  optFace->setFaceFontSize(optFace->fontSize());

  startup->setEnabled(false);
  startup->show();

  RegisterFunction::registerUiClass();

  SDTMainWindow w;
  CombinedWindow w2;
  QObject::connect(&w,SIGNAL(initProgressInfo(int,QString)),startup,SLOT(onProgressMessage(int ,QString)));
  w.init();
  optFace->setFaceStyle(optFace->css());
  w2.insertWindow(&w);
//  w.showMaximized();
  w2.showMaximized();


//  startup->finish(&w);
  startup->finish(&w2);
  delete startup;

  return a.exec();
}
