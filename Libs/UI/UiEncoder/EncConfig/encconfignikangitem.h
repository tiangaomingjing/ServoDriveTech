#ifndef ENCCONFIGNIKANGITEM_H
#define ENCCONFIGNIKANGITEM_H

#include <QObject>
#include <iencconfigitem.h>
class QComboBox;
class EncConfigNiKangItem : public IEncConfigItem
{
  Q_OBJECT
public:
  explicit EncConfigNiKangItem(QObject *parent = 0);
  ~EncConfigNiKangItem();
  void attributeUiInit() Q_DECL_OVERRIDE;
  bool execute()Q_DECL_OVERRIDE;

signals:

public slots:
private:
  QComboBox *m_comboBox;
};

#endif // ENCCONFIGNIKANGITEM_H
