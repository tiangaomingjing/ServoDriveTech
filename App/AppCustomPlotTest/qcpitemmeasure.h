#ifndef QCPITEMMEASURE_H
#define QCPITEMMEASURE_H

#include <QObject>
class QCPItemHandleTag;
class QCustomPlot;
class QCPItemMeasure : public QObject
{
  Q_OBJECT
public:
  typedef enum{
    MEASURE_TYPE_HORIZONTAL,
    MEASURE_TYPE_VERTICAL
  }MeasureType;

  explicit QCPItemMeasure(QCustomPlot *parentPlot,MeasureType type = MEASURE_TYPE_HORIZONTAL,QObject *parent = 0);
  ~QCPItemMeasure();

  void setMeasureScale(qreal scale);
  qreal tag1MeasureData();
  qreal tag2MeasureData();

signals:
  void tag1MeasureDataChanged(qreal data);
  void tag2MeasureDataChanged(qreal data);

public slots:
private:
  QCPItemHandleTag *m_tag1;
  QCPItemHandleTag *m_tag2;
  MeasureType m_type;
  QCustomPlot *m_parentPlot;
  qreal m_scale;
};

#endif // QCPITEMMEASURE_H
