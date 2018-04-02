#ifndef GTPLOT_H
#define GTPLOT_H

#include <QObject>
#include "qcustomplot.h"
class QCPItemHandleTag;

class GtPlot : public QCustomPlot
{
  Q_OBJECT
public:
  explicit GtPlot(QWidget *parent = 0);
  ~GtPlot();

  QCPItemHandleTag *htag;
  QCPItemHandleTag *vtag;

protected:
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
  void currentPosChanged(const QPointF &point);

public slots:
private:
  QPointF m_mouseCurrentPos;
};

#endif // GTPLOT_H
