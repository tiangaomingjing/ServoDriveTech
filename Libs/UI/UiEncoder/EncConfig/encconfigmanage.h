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
  void addEncItem(IEncConfigItem *encItem);
  IEncConfigItem *encItem(quint8 index);
  QStringList itemNames();
  void clearAllEncItem();

  QWidget *curAttributeWidget() const;
  void setCurAttributeWidget(QWidget *w);

signals:

public slots:
private:
  QList<IEncConfigItem*> m_encItemList;
  QWidget *mp_curAttributeWidget;
};

#endif // ENCCONFIGMANAGE_H
