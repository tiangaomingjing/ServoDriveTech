#ifndef WIDGETITEM_H
#define WIDGETITEM_H

#include <QObject>
#include <QGraphicsProxyWidget>


class  WidgetItem : public QGraphicsProxyWidget
{
  Q_OBJECT
public:
  enum PointType{
    POINT_TYPE_LEFT=0,
    POINT_TYPE_RIGHT=1,
    POINT_TYPE_TOP=2,
    POINT_TYPE_BOTTOM=3
  };
  explicit WidgetItem(QGraphicsItem * parent = 0, Qt::WindowFlags wFlags = 0);
  ~WidgetItem();

  void setWidget(QWidget *widget,bool hasWrapWidget = false);
//  QGraphicsProxyWidget *item() const;
  QPointF* pointF(int index) const;

signals:

public slots:
private slots:
  void onGeometryChanged();
private:
//  QGraphicsProxyWidget *m_proxyWidget;
  QList<QPointF*>m_netPoints;
};

#endif // WIDGETITEM_H
