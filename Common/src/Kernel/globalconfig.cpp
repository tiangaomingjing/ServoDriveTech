#include "globalconfig.h"

#include "optautoload.h"
#include "iopt.h"
#include "optcontainer.h"
#include "optface.h"
#include "optplot.h"
#include "optuser.h"


OptContainer *GlobalConfig::m_optc=NULL;

GlobalConfig::GlobalConfig(QObject *parent)
{

}
GlobalConfig::~GlobalConfig()
{

}

void GlobalConfig::init()
{
  OptContainer *optc=OptContainer::instance();

  IOpt *opt=new OptUser("optuser",0);
  optc->addOptItem(opt);
  opt=new OptAutoLoad("optautoload",0);
  optc->addOptItem(opt);
  opt=new OptPlot("optplot",0);
  optc->addOptItem(opt);
  opt=new OptFace("optface",0);
  optc->addOptItem(opt);
  m_optc=optc;
}
OptContainer * GlobalConfig::optContainer()
{
  return m_optc;
}
