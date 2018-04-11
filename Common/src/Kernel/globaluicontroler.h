#ifndef GLOBALUICONTROLER_H
#define GLOBALUICONTROLER_H

#include "iuicontroler.h"

class GlobalConfig;

class GlobalUiControler: public IUiControler
{
  Q_OBJECT
public:
  explicit GlobalUiControler(QList<SevDevice *>&sevList,QObject *parent=0);
  ~GlobalUiControler();

  void createUis()Q_DECL_OVERRIDE;
  IUiWidget *uiWidget(const QString &name);
  void setSevDeviceList(const QList<SevDevice *> &sevList);
signals:
  void sevDeviceListChanged(const QList<SevDevice *> &sevList);
public slots:
private:
  QList<SevDevice *>m_sevList;
};

#endif // GLOBALUICONTROLER_H
