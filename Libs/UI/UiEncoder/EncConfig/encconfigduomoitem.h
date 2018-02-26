#ifndef ENCCONFIGDUOMOITEM_H
#define ENCCONFIGDUOMOITEM_H

#include <QObject>
#include <iencconfigitem.h>

class EncConfigDuoMoItem : public IEncConfigItem
{
  Q_OBJECT
public:
  explicit EncConfigDuoMoItem(QObject *parent = 0);
  ~EncConfigDuoMoItem();

signals:

public slots:
};

#endif // ENCCONFIGDUOMOITEM_H
