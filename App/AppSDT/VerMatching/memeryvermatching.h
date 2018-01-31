#ifndef MEMERYVERMATCHING_H
#define MEMERYVERMATCHING_H

#include <QObject>
#include "ivermatching.h"

//Just for TEST
class MemeryVerMatching : public IVerMatching
{
  Q_OBJECT
public:
  explicit MemeryVerMatching(QObject *parent = 0);
  ~MemeryVerMatching();
  bool open()Q_DECL_OVERRIDE;
  bool close()Q_DECL_OVERRIDE;
private:
  void fillVerLinkLists(QStringList &list)Q_DECL_OVERRIDE;
signals:

public slots:
};

#endif // MEMERYVERMATCHING_H
