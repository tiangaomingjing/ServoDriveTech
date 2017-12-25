#ifndef IOPT_P_H
#define IOPT_P_H
#include <QObject>
class IOpt;

class IOptPrivate
{
  Q_DECLARE_PUBLIC(IOpt)
public:
  IOptPrivate();
  virtual ~IOptPrivate();
  IOpt *q_ptr;
  bool m_isModify;
  QString m_name;
  static QString m_optPath;
};

#endif // IOPT_P_H

