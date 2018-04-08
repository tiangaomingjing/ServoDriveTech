#ifndef GTPLOT_H
#define GTPLOT_H

#include <QObject>
#include "qcustomplot.h"
class QCPItemHandleTag;
class QCPItemMeasure;
class GtPlot : public QCustomPlot
{
  Q_OBJECT
public:
  explicit GtPlot(QWidget *parent = 0);
  ~GtPlot();

  void createHorizMea();
  void createVertiMea();
  void clearHorizMea();
  void clearVertiMea();

protected:
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

signals:
  void currentPosChanged(const QPointF &point);
  void horizMeaDataChanged(qreal v1,qreal v2,qreal dv);
  void vertiMeaDataChanged(qreal v1,qreal v2,qreal dv);

private slots:
  void onHorizMeaDataChanged(qreal data);
  void onVertiMeaDataChanged(qreal data);
private:
  QPointF m_mouseCurrentPos;

  QCPItemMeasure *m_horizMea;
  QCPItemMeasure *m_vertiMea;

};

#endif // GTPLOT_H
