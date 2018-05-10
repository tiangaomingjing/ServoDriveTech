#include "pluginsmanager.h"
#include "gtutils.h"
#include "icurve.h"

#include "ctkPluginException.h"
#include "ctkPluginContext.h"
#include "ctkPluginFramework.h"
#include "ctkPluginFrameworkFactory.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

#define PLUGINLIST_FILE_NAME "plugins.txt"

PluginsManager::PluginsManager(QObject *parent) : QObject(parent),
  m_expertCurve(NULL)
{
  m_frameWorkFactory = new ctkPluginFrameworkFactory;
  QSharedPointer<ctkPluginFramework> framework = m_frameWorkFactory->getFramework();
  try {
      // 初始化并启动插件框架
      framework->init();
      framework->start();
      qDebug() << "CTK Plugin Framework start ...";
  } catch (const ctkPluginException &e) {
      qDebug() << "Failed to initialize the plugin framework: " << e.what();
  }
  m_context = framework->getPluginContext();
}

PluginsManager::~PluginsManager()
{
  delete m_frameWorkFactory;
  m_frameWorkFactory = NULL;
}

bool PluginsManager::loadPlugins()
{
  bool expertOk = installExpertPlugin();
  bool usrOk = installUsrPlugin();
  bool customOk = installCustomPlugin();
  return expertOk&&usrOk&&customOk;
}

QStringList PluginsManager::pluginsFromReadTxt(const QString &fileName)
{
  QStringList list;
  QFile file(fileName);
  QString plugin;
  if(file.open(QFile::ReadOnly|QFile::Text))
  {
    QTextStream in(&file);
    while(!in.atEnd())
    {
      plugin=in.readLine();
      list.append(plugin);
      qDebug()<<"plugin "<<plugin;
    }
    file.close();
  }
  else
    QMessageBox::information(0,tr("error"),tr("error :read file :%1").arg(fileName));

  list.removeAll("");
  return list;
}

bool PluginsManager::installPlugin(const QString &name, const QString &path)
{
  try
  {
      // 安装插件
      QSharedPointer<ctkPlugin> plugin = m_context->installPlugin(QUrl::fromLocalFile(path));
      // 启动插件
      plugin->start(ctkPlugin::START_TRANSIENT);
      m_plugins.insert(name,plugin);
      qDebug() << QString("Plugin = %1  start ...").arg(path);
  }
  catch (const ctkPluginException &e)
  {
    m_plugins.remove(name);
    QMessageBox::information(0,tr("error"),tr("load plugin error:\n%1\n%2").arg(path).arg(e.what()));
    qDebug() << "Failed to install plugin" << e.what();
    return false;
  }
  return true;
}

bool PluginsManager::installExpertPlugin()
{
  QString expertPath = plotPluginsPath()+"expert/";

  QStringList expertPluginsList = pluginsFromReadTxt(expertPath+PLUGINLIST_FILE_NAME);

  if(expertPluginsList.isEmpty())
    return false;
  QString pluginName = expertPluginsList.at(0);
  QString expertPlugin=expertPath+pluginName+".dll";


  if(false==installPlugin("expert",expertPlugin))
    return false;

  //expert 获取服务引用
  ctkServiceReference reference = m_context->getServiceReference<ICurve>();
  if (reference) {
      // 获取指定 ctkServiceReference 引用的服务对象
      ICurve* service = m_context->getService<ICurve>(reference);
      if (service != Q_NULLPTR) {
          // 调用服务
          m_expertCurve=service;
          m_expertCurve->setName("gServo.pro.prm.mot");
          m_expertCurve->setPluginName(pluginName);
          qDebug()<<"expert plugin : display name = "<<m_expertCurve->displayName();
          qDebug()<<"expert plugin : full name = "<<m_expertCurve->fullName();
      }
      else
      {
        QMessageBox::information(0,tr("error"),tr("get service error:ICurve"));
        return false;
      }
  }
  else
  {
    QMessageBox::information(0,tr("error"),tr("get reference error:ICurve"));
    return false;
  }

  return true;
}

QString PluginsManager::plotPluginsPath()
{
  QString plotPluginsPath=GTUtils::customPath()+"plugins/plot/";

  return plotPluginsPath;
}

bool PluginsManager::installUsrPlugin()
{
  QString usrPath=plotPluginsPath()+"user/";

  QStringList usrPluginsList=pluginsFromReadTxt(usrPath+PLUGINLIST_FILE_NAME);
  bool ret = true;

  if(usrPluginsList.isEmpty())
    return true;


  for(int i = 0;i< usrPluginsList.size();i++)
  {
    QString usrPlugin;
    QString pluginName;
    bool ok = true;
    pluginName = usrPluginsList.at(i);
    usrPlugin = usrPath + pluginName +".dll";
    ok = installPlugin("usr",usrPlugin);
    qDebug()<<"installPlugin OK = "<<ok;
    if(ok)
    {
     //expert 获取服务引用
      QString filter = QString("(name=%1)").arg(pluginName);
      QList<ctkServiceReference> references = m_context->getServiceReferences<ICurve>(filter);
      qDebug()<<"references size = "<<references.size();
      if(!references.isEmpty())
      {
        ctkServiceReference reference = references.at(0);
        if (reference)
        {
          // 获取指定 ctkServiceReference 引用的服务对象
          ICurve* service = m_context->getService<ICurve>(reference);
          if (service != Q_NULLPTR) {
            // 调用服务
            m_usrCurves.append(service);
            service->setPluginName(pluginName);
            qDebug()<<"usr plugin : display name = "<<service->displayName();
            qDebug()<<"usr plugin : full name = "<<service->fullName();
          }
          else
          {
            QMessageBox::information(0,tr("error"),tr("get service error:m_context->getService"));
            ret = false;
          }
        }
      }
      else
      {
        QMessageBox::information(0,tr("error"),tr("error:m_context->getServiceReferences is Empty"));
        ret = false;
      }
    }
    else
    {
      QMessageBox::information(0,tr("error"),tr("error:installPlugin = %1").arg(usrPlugin));
      ret = false;
    }

  }

  return ret;


}

bool PluginsManager::installCustomPlugin()
{
  return true;
}

QList<QList<ICurve *> > PluginsManager::customCurves() const
{
  return m_customCurves;
}

QList<ICurve *> PluginsManager::usrCurves() const
{
  return m_usrCurves;
}

ICurve *PluginsManager::expertCurve() const
{
  return m_expertCurve;
}

