#ifndef ENCCONFIGHAIDEHANITEM_H
#define ENCCONFIGHAIDEHANITEM_H

#include <QObject>
#include <iencconfigitem.h>

class EncConfigHaidehanItem : public IEncConfigItem
{
  Q_OBJECT
public:
  explicit EncConfigHaidehanItem(QObject *parent = 0);
  ~EncConfigHaidehanItem();

signals:

public slots:
};

#endif // ENCCONFIGHAIDEHANITEM_H
