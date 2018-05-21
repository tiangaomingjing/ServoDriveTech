#ifndef PLUGINSMANAGER_H
#define PLUGINSMANAGER_H

#include <QObject>
#include <QMultiMap>
#include <QList>
#include "ctkPlugin.h"

class ICurve;
class ctkPluginContext;
class ctkPluginFrameworkFactory;

class PluginsManager : public QObject
{
  Q_OBJECT
public:
  explicit PluginsManager(QObject *parent = 0);
  ~ PluginsManager();

  bool loadPlugins();

  ICurve *expertCurve() const;

  QList<ICurve *> usrCurves() const;

  QList<QList<ICurve *> > customCurves() const;

  void saveCurvesToXml(const QList<ICurve *> &clist);
  QList<ICurve *> buildCurvesFromXml();

private:
  QStringList pluginsFromReadTxt(const QString &fileName);
  QString plotPluginsPath();
  bool installPlugin(const QString &name,const QString &path);

  bool installExpertPlugin();
  bool installUsrPlugin();
  bool installCustomPlugin();

  ICurve *createICurveFromContainer(const QString &name);

signals:

public slots:
private:
  ctkPluginFrameworkFactory *m_frameWorkFactory;
  ctkPluginContext* m_context;

  QMultiMap<QString,QSharedPointer<ctkPlugin>>m_plugins;

  QList<ICurve *>m_usrCurves;
  ICurve *m_expertCurve;
  QList<QList<ICurve *>>m_customCurves;

};

#endif // PLUGINSMANAGER_H
