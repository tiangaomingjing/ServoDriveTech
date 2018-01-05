#ifndef GLOBALUICONTROLER_H
#define GLOBALUICONTROLER_H

#include "iuicontroler.h"

class GlobalConfig;

class GlobalUiControler: public IUiControler
{
  Q_OBJECT
public:
  explicit GlobalUiControler(OptContainer *gconfig, QObject *parent=0);
  ~GlobalUiControler();

  void createUis()Q_DECL_OVERRIDE;
  IUiWidget *getUiWidgetByClassName(const QString &name);
signals:
public slots:
};

#endif // GLOBALUICONTROLER_H
