#ifndef SDTERROR_H
#define SDTERROR_H

#include <QObject>
class  SdtError
{
public:
  static SdtError *instance()
  {
    static QMutex mutex;
    if(!m_instance)
    {
      QMutexLocker locker(&mutex);
      if(!m_instance)
        m_instance=new SdtError();
    }
    return m_instance;
  }

  ~SdtError(){}

  static QStringList *errorStringList()
  {
    return &m_errList;
  }
protected:
  SdtError(){}
private:
  static QStringList m_errList;
  static SdtError *m_instance;
};

#endif // SDTERROR_H
