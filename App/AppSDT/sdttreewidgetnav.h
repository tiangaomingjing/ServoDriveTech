#ifndef SDTTREEWIDGETNAV_H
#define SDTTREEWIDGETNAV_H

#include <QTreeWidget>

class SdtTreeWidgetNav : public QTreeWidget
{
  Q_OBJECT
public:
  explicit SdtTreeWidgetNav(QWidget *parent = 0);
  void updateSizeHint(QSize & szHint2Set);
  virtual QSize sizeHint() const;

signals:

public slots:
protected:
  QSize m_szHint;
};

#endif // SDTTREEWIDGETNAV_H
