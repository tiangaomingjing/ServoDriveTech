#ifndef ENCCONFIGYASKAWAITEM_H
#define ENCCONFIGYASKAWAITEM_H

#include <QObject>
#include <iencconfigitem.h>

class EncConfigYaskawaItem : public IEncConfigItem
{
  Q_OBJECT
public:
  explicit EncConfigYaskawaItem(QObject *parent = 0);
  ~EncConfigYaskawaItem();

signals:

public slots:
};

#endif // ENCCONFIGYASKAWAITEM_H
