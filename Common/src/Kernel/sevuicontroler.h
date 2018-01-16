#ifndef SEVUICONTROLER_H
#define SEVUICONTROLER_H

#include "iuicontroler.h"

class OptContainer;
class IUiWidget;
class SevUiControler : public IUiControler
{
  Q_OBJECT
public:
  explicit SevUiControler(SevDevice *sev,QObject *parent=0);
  ~SevUiControler();
  void createUis()Q_DECL_OVERRIDE;
  IUiWidget *uiWidget(quint32 devInx,qint16 axisInx,const QString &uiName) const;

signals:

public slots:
private:
  SevDevice *m_sev;
};

#endif // SEVUICONTROLER_H
