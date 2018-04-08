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
  typedef enum{
    SELECT_STATE_NONE,
    SELECT_STATE_SINGLE,
    SELECT_STATE_ALL
  }SelectState;

  explicit QCPItemMeasure(QCustomPlot *parentPlot,MeasureType type = MEASURE_TYPE_HORIZONTAL,QObject *parent = 0);
  ~QCPItemMeasure();

  void initPosition();
  qreal tag1MeasureData() const;
  qreal tag2MeasureData() const;
  qreal dTagMeasureData() const;

  QCPItemHandleTag *tag1() const;
  QCPItemHandleTag *tag2() const;

public slots:
private slots:
  void onTagSelectChanged();
  void onTag1DataChanged(qreal data);
  void onTag2DataChanged(qreal data);
private:
  QCPItemHandleTag *m_tag1;
  QCPItemHandleTag *m_tag2;
  MeasureType m_type;
  QCustomPlot *m_parentPlot;
  SelectState m_selectState;
  qreal m_dv;
  qreal m_dPrev1;
  qreal m_dPrev2;
};

#endif // QCPITEMMEASURE_H
