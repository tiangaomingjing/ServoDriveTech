#ifndef SDASSEMBLY_H
#define SDASSEMBLY_H

#include <QObject>

class GlobalConfig;
class SevDevice;
class IUiControler;

class SdAssembly : public QObject
{
  Q_OBJECT
public:
  explicit SdAssembly(SevDevice *sev,IUiControler *ui,QObject *parent=0):QObject(parent),\
    m_device(sev),m_uiControler(ui)
  {}
  ~SdAssembly(){}
  SevDevice *m_device;
  IUiControler *m_uiControler;

signals:

public slots:
};

#endif // SDASSEMBLY_H
