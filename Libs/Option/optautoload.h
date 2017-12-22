#ifndef OPTAUTOLOAD_H
#define OPTAUTOLOAD_H

#include <QObject>
#include "iopt.h"
namespace Ui {
class OptAutoLoad;
}
class OptAutoLoadPrivate;

class OptAutoLoad : public IOpt
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(OptAutoLoad)
public:
  explicit OptAutoLoad(const QString &optName,QWidget *parent = 0);
  ~OptAutoLoad();
  bool optActive();

signals:

public slots:
private:
  Ui::OptAutoLoad *ui;
};

#endif // OPTAUTOLOAD_H
