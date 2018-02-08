#ifndef ENCCONFIGMANAGE_H
#define ENCCONFIGMANAGE_H

#include <QObject>
class IEncConfigItem;

class EncConfigManage : public QObject
{
  Q_OBJECT
public:
  explicit EncConfigManage(QObject *parent = 0);
  ~EncConfigManage();
  void addEncConfigItem(IEncConfigItem *encItem);
  IEncConfigItem *encConfigItem(quint8 index);
  QStringList itemNames();
  void clearAllEncConfigItem();

signals:

public slots:
private:
  QList<IEncConfigItem*> m_encItemList;
};

#endif // ENCCONFIGMANAGE_H
