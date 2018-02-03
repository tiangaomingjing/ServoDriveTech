#ifndef DBVERMATCHING_H
#define DBVERMATCHING_H

#include <QObject>
#include "ivermatching.h"

class DbVerMatching : public IVerMatching
{
  Q_OBJECT
public:
  explicit DbVerMatching(QObject *parent = 0);
  ~DbVerMatching();
  bool open()Q_DECL_OVERRIDE;
  bool close()Q_DECL_OVERRIDE;
private:
  void fillVerLinkLists(QStringList &list)Q_DECL_OVERRIDE;
  bool hasComponent(const VerInfo &verinfo)Q_DECL_OVERRIDE;

signals:

public slots:
private:

};

#endif // DBVERMATCHING_H
