#ifndef SDASSEMBLY_H
#define SDASSEMBLY_H

#include <QObject>

namespace GT {
class GlobalConfig;
}
class SevDevice;
class IUiControler;
class SdAssembly : public QObject
{
  Q_OBJECT
public:
  explicit SdAssembly(QObject *parent=0):QObject(parent){}
  ~SdAssembly();
  SevDevice *m_device;
  IUiControler *m_uiControler;
  GT::GlobalConfig *m_gConfig;

signals:

public slots:
};

#endif // SDASSEMBLY_H
