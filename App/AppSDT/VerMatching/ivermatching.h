#ifndef IVERMATCHING_H
#define IVERMATCHING_H

#include <QObject>

class IVerMatching : public QObject
{
  Q_OBJECT
public:
  explicit IVerMatching(QObject *parent = 0);
  virtual ~IVerMatching();
  virtual bool open()=0;
  bool check(quint32 p,quint32 c,quint32 v,quint32 f);
  virtual bool close()=0;
  QStringList *verLinkLists();

signals:


public slots:

protected:
  virtual void fillVerLinkLists(QStringList &list)=0;
protected:
  QStringList m_verLinkLists;
};

#endif // IVERMATCHING_H
