#ifndef PLUGINFRAMEWORKMAINWINDOW_H
#define PLUGINFRAMEWORKMAINWINDOW_H

#include <QMainWindow>
#include "ctkPlugin.h"
#include "ctkPluginFrameworkFactory.h"

namespace Ui {
class PluginFrameworkMainWindow;
}
class IPlotCurve;
class ctkPluginContext;
class PluginFrameworkMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit PluginFrameworkMainWindow(QWidget *parent = 0);
  ~PluginFrameworkMainWindow();

private slots:
  void on_actionStopPlugin_triggered();

  void on_actionStartPlugin_triggered();

  void on_actionDeleteFactory_triggered();

private:
  Ui::PluginFrameworkMainWindow *ui;

  QList<QSharedPointer<ctkPlugin>> plugins;
  QList<IPlotCurve*>curves;
  ctkPluginContext* context;
  ctkPluginFrameworkFactory *frameWorkFactory;
};

#endif // PLUGINFRAMEWORKMAINWINDOW_H
