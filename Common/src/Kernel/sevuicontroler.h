#ifndef SEVUICONTROLER_H
#define SEVUICONTROLER_H

#include "iuicontroler.h"

class OptContainer;
class SevUiControler : public IUiControler
{
  Q_OBJECT
public:
  explicit SevUiControler(SevDevice *sev,OptContainer *gconfig,QObject *parent=0);
  ~SevUiControler();
  void createUis()Q_DECL_OVERRIDE;
signals:

public slots:
private:
  SevDevice *m_sev;
};

#endif // SEVUICONTROLER_H
