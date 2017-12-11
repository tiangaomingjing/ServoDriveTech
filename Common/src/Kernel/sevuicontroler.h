#ifndef SEVUICONTROLER_H
#define SEVUICONTROLER_H

#include "iuicontroler.h"


class SevUiControler : public IUiControler
{
  Q_OBJECT
public:
  explicit SevUiControler(SevDevice *sev,GlobalConfig *gconfig,QObject *parent=0);
  ~SevUiControler();
  void createUis()Q_DECL_OVERRIDE;
signals:

public slots:
};

#endif // SEVUICONTROLER_H
