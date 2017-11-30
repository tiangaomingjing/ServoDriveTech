#ifndef SEVUICONTROLER_H
#define SEVUICONTROLER_H

#include <QObject>
#include "iuicontroler.h"


class SevUiControler : public IUiControler
{
  Q_OBJECT
public:
  explicit SevUiControler(SevDevice *sev,GT::GlobalConfig *gconfig,QObject *parent=0):IUiControler(sev,gconfig,parent){}
  ~SevUiControler(){}
signals:

public slots:
};

#endif // SEVUICONTROLER_H
