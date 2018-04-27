#include <QApplication>
#include "pluginsmanager.h"
#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  PluginsManager manager;
  manager.loadPlugins();


  //test to find devid
  QList<int >curves;
  curves<<1<<1<<0<<0<<0<<2<<1<<1<<2<<2<<2<<2<<3<<5<<5<<5<<5<<1<<1<<1<<1;

  QList<int> devs;
  for(int i=0;i<curves.size();i++)
  {
    int dev=curves.at(i);
    if(devs.isEmpty())
    {
      devs.append(dev);
      continue;
    }
    else
    {
      bool has=false;
      for(int j=0;j<devs.size();j++)
      {
        if(dev==devs.at(j))
        {
          has=true;
          break;
        }
      }
      if(has==false)
        devs.append(dev);
    }
  }

  foreach (int v, devs) {
    qDebug()<<v;
  }


  QList<int> dsps;
  curves.clear();
  qDebug()<<"dsp test";
  curves<<1<<0<<1<<1<<2<<2<<2;
  for(int i=0;i<curves.size();i++)
  {
    int d=curves.at(i);
    if(dsps.isEmpty())
    {
      dsps.append(d);
    }
    else
    {
      bool has=false;
      for(int j=0;j<dsps.size();j++)
      {
        if(d==dsps.at(j))
        {
          has=true;
          break;
        }
      }
      if(has==false)
        dsps.append(d);
    }
  }

  foreach (int v, dsps) {
    qDebug()<<v;
  }

  return a.exec();
}

