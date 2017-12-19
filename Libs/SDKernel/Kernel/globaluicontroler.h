#ifndef GLOBALUICONTROLER_H
#define GLOBALUICONTROLER_H

#include "iuicontroler.h"

class GlobalUiControler: public IUiControler
{
  Q_OBJECT
public:
  explicit GlobalUiControler(GlobalConfig *gconfig,QObject *parent=0);
  ~GlobalUiControler();

  void createUis()Q_DECL_OVERRIDE;
signals:
public slots:
};

#endif // GLOBALUICONTROLER_H
