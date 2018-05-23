#ifndef UIMOTIONVELOCITY_H
#define UIMOTIONVELOCITY_H

#include <QWidget>

namespace Ui {
class UiMotionVelocity;
}
class UiMotionData
{
public:
  UiMotionData():
    m_isCircle(false),
    m_seqAmp(5),
    m_seqPeriod(200),
    m_seqCircleCount(10),
    m_stepAmp(5),
    m_stepTime(5)
  {}
  ~UiMotionData(){}
  bool m_isCircle;
  int m_seqAmp;
  int m_seqPeriod;
  int m_seqCircleCount;
  int m_stepAmp;
  int m_stepTime;
};

class MotionVelocity;

class UiMotionVelocity : public QWidget
{
  Q_OBJECT

public:
  explicit UiMotionVelocity(int axisCount , QWidget *parent = 0);
  ~UiMotionVelocity();
  void updataUi(int axisInx);

protected:
  bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

private slots:
  void onCheckBoxCircleSWClicked();
  void onCssChanged(const QString &css);
private:
  void setupIcons(const QString &css);

private:
  Ui::UiMotionVelocity *ui;
  int m_axisCount;
  QList<UiMotionData*>m_uiDataList;
};

#endif // UIMOTIONVELOCITY_H
