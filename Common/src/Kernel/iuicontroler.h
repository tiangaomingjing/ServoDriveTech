#ifndef IUICONTROLER_H
#define IUICONTROLER_H

#include <QObject>
namespace GT {
class GlobalConfig;
}
class SevDevice;
class IUiControler : public QObject
{
  Q_OBJECT
public:
  explicit IUiControler(SevDevice *sev,GT::GlobalConfig *gconfig,QObject *parent=0):QObject(parent)\
  ,m_sev(sev),m_gConfig(gconfig){}
  virtual ~IUiControler(){}
  SevDevice *m_sev;
  GT::GlobalConfig *m_gConfig;

signals:

public slots:
};

#endif // IUICONTROLER_H
