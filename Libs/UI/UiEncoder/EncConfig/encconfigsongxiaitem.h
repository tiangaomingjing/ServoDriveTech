#ifndef ENCCONFIGSONGXIAITEM_H
#define ENCCONFIGSONGXIAITEM_H

#include <QObject>
#include <iencconfigitem.h>

class EncConfigSongXiaItem : public IEncConfigItem
{
  Q_OBJECT
public:
  explicit EncConfigSongXiaItem(QObject *parent = 0);
  ~EncConfigSongXiaItem();

signals:

public slots:
};

#endif // ENCCONFIGSONGXIAITEM_H
