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
  static OptContainer *instance(QObject *parent=0);
  ~OptContainer();
  void addOptItem(IOpt*opt);
  IOpt* optItem(const QString &optName);
  QList<IOpt*> optItems();
  void saveOpt();
protected:
  OptContainer(QObject *parent=0);

signals:
public slots:
private:
  //防止默认拷贝构造函数发生
  OptContainer(OptContainer &oc){}
  static QHash<QString,IOpt*>m_optHash;
  static OptContainer* m_instance;
  QList<IOpt*> m_optList;

};

#endif // OPTION_H
