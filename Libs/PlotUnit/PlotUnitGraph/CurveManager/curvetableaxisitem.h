#ifndef CURVETABLEAXISITEM_H
#define CURVETABLEAXISITEM_H

#include <QWidget>
class QLabel;
class QComboBox;
class ICurve;
class CurveTableAxisItem : public QWidget
{
  Q_OBJECT
public:
  explicit CurveTableAxisItem(QWidget *parent = 0);

  QLabel *m_label;
  QComboBox *m_box;
  ICurve *m_curve;

signals:

public slots:
private:

};

#endif // CURVETABLEAXISITEM_H
