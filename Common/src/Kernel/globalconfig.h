#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

#include <QObject>

class OptContainer;
class GlobalConfig:public QObject
{
  Q_OBJECT
public:
  explicit GlobalConfig(QObject *parent=0);
  ~GlobalConfig();
  void init();
  static OptContainer * optContainer();
private:
  static OptContainer *m_optc;
};

#endif // GLOBALCONFIG_H
