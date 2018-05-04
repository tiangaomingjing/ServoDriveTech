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
  QString plotPluginsPath=GTUtils::customPath()+"plugins/plot/";
  QString usrPath=plotPluginsPath+"user/";
  QString expertPath=plotPluginsPath+"expert/";
//  QString customPath=plotPluginsPath+"custom/";

  QStringList usrPluginsList=pluginsFromReadTxt(usrPath+PLUGINLIST_FILE_NAME);
  QStringList expertPluginsList=pluginsFromReadTxt(expertPath+PLUGINLIST_FILE_NAME);

  if(expertPluginsList.isEmpty())
    return false;
  QString expertPlugin=expertPath+expertPluginsList.at(0);
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
          qDebug()<<"display name"<<m_expertCurve->displayName();
          qDebug()<<"full name"<<m_expertCurve->fullName();
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
  qDebug()<<"plugin path"<<path;
  try
  {
      // 安装插件
      QSharedPointer<ctkPlugin> plugin = m_context->installPlugin(QUrl::fromLocalFile(path));
      // 启动插件
      plugin->start(ctkPlugin::START_TRANSIENT);
      m_plugins.insert(name,plugin);
      qDebug() << "Plugin start ...";
  }
  catch (const ctkPluginException &e)
  {
    QMessageBox::information(0,tr("error"),tr("load plugin error:\n%1\n%2").arg(path).arg(e.what()));
    qDebug() << "Failed to install plugin" << e.what();
    return false;
  }
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

