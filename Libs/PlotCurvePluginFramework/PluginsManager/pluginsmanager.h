#ifndef PLUGINSMANAGER_H
#define PLUGINSMANAGER_H

#include <QObject>
#include <QHash>
#include <QList>
#include "ctkPlugin.h"
#include "ctkPluginFrameworkFactory.h"

class ICurve;
class ctkPluginContext;

class PluginsManager : public QObject
{
  Q_OBJECT
public:
  explicit PluginsManager(QObject *parent = 0);
  bool loadPlugins();

  ICurve *expertCurve() const;

  QList<ICurve *> usrCurves() const;

  QList<QList<ICurve *> > customCurves() const;

private:
  QStringList pluginsFromReadTxt(const QString &fileName);
  bool installPlugin(const QString &name,const QString &path);
signals:

public slots:
private:
  ctkPluginFrameworkFactory m_frameWorkFactory;
  ctkPluginContext* m_context;

  QHash<QString,QSharedPointer<ctkPlugin>>m_plugins;

  QList<ICurve *>m_usrCurves;
  ICurve *m_expertCurve;
  QList<QList<ICurve *>>m_customCurves;
};

#endif // PLUGINSMANAGER_H
