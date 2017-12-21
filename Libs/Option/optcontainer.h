#ifndef OPTION_H
#define OPTION_H

#include "option_global.h"
#include <QObject>
#include <QHash>
#include "iopt.h"
class IOpt;
//sigleton object
class OPTIONSHARED_EXPORT OptContainer:public QObject
{
  Q_OBJECT
public:
  explicit OptContainer(QObject *parent=0);
  ~OptContainer();
  void addOptItem(IOpt*opt);
  IOpt* optItem(const QString &optName);
  void saveOpt();

signals:
public slots:
private:
static QHash<QString,IOpt*>m_optHash;
static int aa;
};

#endif // OPTION_H
