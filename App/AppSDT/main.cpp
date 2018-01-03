#include "sdtmainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

#include "optautoload.h"
#include "iopt.h"
#include "optcontainer.h"
#include "optface.h"
#include "optplot.h"
#include "optuser.h"

#include "gtutils.h"

#include "registerfunction.h"

#include "screenstartup.h"

#define START_UP_PIXMAP "startup.png"

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

  opt=optc->optItem("optface");
  OptFace *optFace=dynamic_cast<OptFace *>(opt);

  QString pixPath=GTUtils::customPath()+"option/style/"+optFace->css()+"/icon/"+START_UP_PIXMAP;
  qDebug()<<"pixPath"<<pixPath;
  QPixmap pixmap(pixPath);
  ScreenStartup *startup=new ScreenStartup(pixmap);

  QString langPath=GTUtils::languagePath();
  QString lang;
  if(optFace->language()=="chinese")
  {
    lang=langPath+"ch_main.qm";
  }
  else
  {
    lang=langPath+"en_main.qm";
  }
  optFace->setFaceStyle(optFace->css());
  optFace->setFaceFontSize(optFace->fontSize());

  startup->show();
  qDebug()<<"language "<<lang;
  QTranslator trans;
  trans.load(lang);
  a.installTranslator(&trans);

  RegisterFunction::registerUiClass();

  SDTMainWindow w;
  QObject::connect(&w,SIGNAL(initProgressInfo(int,QString)),startup,SLOT(onProgressMessage(int ,QString)));
  w.init();
  w.showMaximized();

  startup->finish(&w);
  delete startup;

  return a.exec();
}
