#ifndef PIDITEM_H
#define PIDITEM_H

#include <QObject>
#include <QGraphicsWidget>
class QGraphicsProxyWidget;

class PidItem : public QObject
{
  Q_OBJECT
public:
  enum PointType{
    POINT_TYPE_LEFT=0,
    POINT_TYPE_RIGHT=1,
    POINT_TYPE_TOP=2,
    POINT_TYPE_BOTTOM=3
  };
  explicit PidItem(QObject *parent = 0);
  ~PidItem();

  void setWidget(QWidget *widget);
  QGraphicsProxyWidget *item();

signals:

public slots:
private:
  bool eventFilter(QObject *obj, QEvent *e) Q_DECL_OVERRIDE;

private:
  QGraphicsProxyWidget *m_proxyWidget;
  QList<QPointF>m_netPoints;
};

#endif // PIDITEM_H
