#ifndef ENCCONFIGSANXIEITEM_H
#define ENCCONFIGSANXIEITEM_H

#include <QObject>
#include <iencconfigitem.h>

class EncConfigSanXieItem:public IEncConfigItem
{
Q_OBJECT
public:
  explicit EncConfigSanXieItem(QObject *parent = 0);
  ~EncConfigSanXieItem();
signals:

public slots:
};

#endif // ENCCONFIGSANXIEITEM_H
