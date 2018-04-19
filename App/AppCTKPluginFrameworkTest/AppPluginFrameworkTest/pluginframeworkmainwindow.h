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
class QTreeWidget;
class QTreeWidgetItem;
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

  void on_actionClone_triggered();

  void on_actionShowCloneObj_triggered();
  void on_actionVectorTest_triggered();

private:
  QVector<double> &vec();//test

  void loadFiles(QString path, QTreeWidget *treewidget, QTreeWidgetItem *item) ;
private:
  Ui::PluginFrameworkMainWindow *ui;

  QList<QSharedPointer<ctkPlugin>> plugins;
  QList<IPlotCurve*>curves;
  QList<IPlotCurve*>cloneCurves;
  ctkPluginContext* context;
  ctkPluginFrameworkFactory *frameWorkFactory;

  QVector<double> vector;
};

#endif // PLUGINFRAMEWORKMAINWINDOW_H
