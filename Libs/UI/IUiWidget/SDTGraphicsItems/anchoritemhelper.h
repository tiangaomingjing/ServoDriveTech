#ifndef ANCHORITEMHELPER_H
#define ANCHORITEMHELPER_H

#include <QObject>
#include "sdtgraphicsitems_global.h"

class QGraphicsItem;
class SDTGRAPHICSITEMSSHARED_EXPORT AnchorItemHelper : public QObject
{
  Q_OBJECT
public:
  enum AnchorPoint {
      AnchorLeft = 0,
      AnchorHorizontalCenter,
      AnchorRight,
      AnchorTop,
      AnchorVerticalCenter,
      AnchorBottom
  };

  explicit AnchorItemHelper(QObject *parent = 0);
  ~AnchorItemHelper();
  void addAnchor(QGraphicsItem *originItem,QGraphicsItem *targetItem,AnchorPoint anchorPoint,qreal space = 0);
  void setAnchorsActive();
signals:

public slots:
private:
  class AnchorData;
  QList<AnchorData *>m_anchorDatas;
};

#endif // ANCHORITEMHELPER_H
