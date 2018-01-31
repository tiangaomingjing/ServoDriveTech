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
  enum CheckStatus{
    CHECK_STA_OK,
    CHECK_STA_NSUPPORT,
    CHECK_STA_SOFT_OLD
  };

  explicit IVerMatching(QObject *parent = 0);
  virtual ~IVerMatching();
  virtual bool open()=0;
  CheckStatus check(const VerInfo &verinfo);
  virtual bool close()=0;
  QStringList *verLinkLists();

signals:


public slots:

protected:
  virtual void fillVerLinkLists(QStringList &list)=0;
  virtual bool hasComponent(const VerInfo &verinfo)=0;
protected:
  QStringList m_verLinkLists;
};

#endif // IVERMATCHING_H
