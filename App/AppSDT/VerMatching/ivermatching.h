#ifndef IVERMATCHING_H
#define IVERMATCHING_H

#include <QObject>
class VerInfo
{
public:
  VerInfo(){}
  ~VerInfo(){}
  quint32 c;
  quint32 v;
  quint32 f;
  quint32 p;
};
class IVerMatching : public QObject
{
  Q_OBJECT
public:
  explicit IVerMatching(QObject *parent = 0);
  virtual ~IVerMatching();
  virtual bool open()=0;
  bool check(const VerInfo &verinfo);
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
