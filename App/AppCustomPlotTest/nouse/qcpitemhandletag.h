#ifndef QCPITEMHANDLETAG_H
#define QCPITEMHANDLETAG_H

#include <QObject>
#include "qcustomplot.h"
class QCPItemHandleTag:public QCPItemText
{
  Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
  Q_PROPERTY(QColor textSelectColor READ textSelectColor WRITE setTextSelectColor NOTIFY textSelectColorChanged)
  Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
  Q_PROPERTY(QColor backgroundSelectColor READ backgroundSelectColor WRITE setBackgroundSelectColor NOTIFY backgroundSelectColorChanged)

  Q_OBJECT
public:
 typedef enum{
    HANDLE_TAG_TYPE_HORIZONTAL,
    HANDLE_TAG_TYPE_VERTICAL
  }HandleTagType;

  explicit QCPItemHandleTag(QCustomPlot *parentPlot,HandleTagType type = HANDLE_TAG_TYPE_HORIZONTAL);
  ~QCPItemHandleTag();

  QColor textColor() const;
  void setTextColor(const QColor &textColor);

  QColor textSelectColor() const;
  void setTextSelectColor(const QColor &textSelectColor);

  QColor backgroundColor() const;
  void setBackgroundColor(const QColor &backgroundColor);

  QColor backgroundSelectColor() const;
  void setBackgroundSelectColor(const QColor &backgroundSelectColor);

  qreal currentData() const;
  void setCurrentData(qreal data);

signals:
  void textColorChanged(const QColor &color);
  void textSelectColorChanged(const QColor &color);
  void backgroundColorChanged(const QColor &color);
  void backgroundSelectColorChanged(const QColor &color);

  void currentDataChanged(qreal data);

protected:
  void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  void mousePressEvent(QMouseEvent *event, const QVariant &details) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;
  void mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos) Q_DECL_OVERRIDE;

  void setColorStyle();

  QColor m_textColor;
  QColor m_textSelectColor;
  QColor m_backgroundColor;
  QColor m_backgroundSelectColor;

  qreal m_currentData;
  HandleTagType m_type;
};

#endif // QCPITEMHANDLETAG_H
