#ifndef IOPT_H
#define IOPT_H

#include <QWidget>
#include "option_global.h"
class IOptPrivate;
class OPTIONSHARED_EXPORT IOpt : public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IOpt)
public:
  explicit IOpt(const QString &optName, QWidget *parent = 0);
  virtual ~IOpt();
  QString name() const;
  bool isModify() const;
  void setModify(bool modify);
  bool execute();
  virtual bool optActive()=0;

signals:

public slots:
protected:
  IOpt(const QString &optName, IOptPrivate&dd, QWidget *parent = 0);
protected:
  IOptPrivate *d_ptr;

};

#endif // IOPT_H
