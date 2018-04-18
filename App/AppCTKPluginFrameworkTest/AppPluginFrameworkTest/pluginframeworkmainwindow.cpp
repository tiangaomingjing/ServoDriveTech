#include "pluginframeworkmainwindow.h"
#include "ui_pluginframeworkmainwindow.h"


#include "ctkPluginFramework.h"
#include "ctkPluginException.h"
#include "ctkPluginContext.h"

#include "iplotcurve.h"

#include <QDebug>
#include <QDirIterator>

PluginFrameworkMainWindow::PluginFrameworkMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::PluginFrameworkMainWindow)
{
  ui->setupUi(this);

//  ctkPluginFrameworkFactory frameWorkFactory;
  frameWorkFactory=new ctkPluginFrameworkFactory;
  QSharedPointer<ctkPluginFramework> framework = frameWorkFactory->getFramework();
  try {
      // 初始化并启动插件框架
      framework->init();
      framework->start();
      qDebug() << "CTK Plugin Framework start ...";
  } catch (const ctkPluginException &e) {
      qDebug() << "Failed to initialize the plugin framework: " << e.what();
//      return -1;
  }

  // 获取插件上下文
  context = framework->getPluginContext();

  // 获取插件所在位置
  QString path = QCoreApplication::applicationDirPath() + "/plugins/test";

  // 遍历路径下的所有插件
  QDirIterator itPlugin(path, QStringList() << "*.dll" << "*.so", QDir::Files);
  while (itPlugin.hasNext()) {
      QString strPlugin = itPlugin.next();
      try {
          // 安装插件
          QSharedPointer<ctkPlugin> plugin = context->installPlugin(QUrl::fromLocalFile(strPlugin));
          // 启动插件
          plugin->start(ctkPlugin::START_TRANSIENT);
          plugins.append(plugin);
          qDebug() << "Plugin start ...";
      } catch (const ctkPluginException &e) {
          qDebug() << "Failed to install plugin" << e.what();
//          return -1;
      }
  }

  // 获取服务引用
//  ctkServiceReference reference = context->getServiceReference<IPlotCurve>();
//  if (reference) {
//      // 获取指定 ctkServiceReference 引用的服务对象
//      IPlotCurve* service = context->getService<IPlotCurve>(reference);
//      if (service != Q_NULLPTR) {
//          // 调用服务
//          service->sayHello();
//      }
//  }

//  QList<ctkServiceReference> references = context->getServiceReferences<IPlotCurve>("(name=PlotCurveRaw)");
  QList<ctkServiceReference> references = context->getServiceReferences<IPlotCurve>();
  ctkServiceReference ref;
  for(int i=0;i<references.size();i++)
  {
    ref=references.at(i);

    if (ref)
    {
      qDebug()<<"property name"<<ref.getProperty("name").toString();
      // 获取指定 ctkServiceReference 引用的服务对象
      IPlotCurve* service = context->getService<IPlotCurve>(ref);
      if (service != Q_NULLPTR)
      {
        // 调用服务
        curves.append(service);
        service->sayHello();

      }
    }
  }

}

PluginFrameworkMainWindow::~PluginFrameworkMainWindow()
{
  delete ui;
}

void PluginFrameworkMainWindow::on_actionStopPlugin_triggered()
{
  for(int i=0;i<plugins.size();i++)
  {
    plugins.at(i)->stop(ctkPlugin::STOP_TRANSIENT);
  }
  curves.clear();
}

void PluginFrameworkMainWindow::on_actionStartPlugin_triggered()
{

  for(int i=0;i<plugins.size();i++)
  {
    qDebug()<<"start"<<i;
    plugins.at(i)->start(ctkPlugin::START_TRANSIENT);
  }

  qDebug()<<"aaaaaaaaa";
  QList<ctkServiceReference> references = context->getServiceReferences<IPlotCurve>();
  qDebug()<<"aaaaaaaaa";
  ctkServiceReference ref;
  for(int i=0;i<references.size();i++)
  {
    ref=references.at(i);

    if (ref)
    {
//      qDebug()<<"property name"<<ref.getProperty("name").toString();
      // 获取指定 ctkServiceReference 引用的服务对象
      IPlotCurve* service = context->getService<IPlotCurve>(ref);
      if (service != Q_NULLPTR)
      {
        // 调用服务
        curves.append(service);
        service->sayHello();

      }
    }
  }

  for(int i=0;i<curves.size();i++)
  {
    curves.at(i)->sayHello();
//    delete curves.at(i);
  }
//  curves.clear();
}

void PluginFrameworkMainWindow::on_actionDeleteFactory_triggered()
{
  if(frameWorkFactory)
  {
    delete frameWorkFactory;//经验证，删除时不会释放所有的插件服务对象，plugin没有了，服务对象还有
    frameWorkFactory=NULL;
  }

  for(int i=0;i<curves.size();i++)
  {
    curves.at(i)->sayHello();
//    delete curves.at(i);
  }
}
