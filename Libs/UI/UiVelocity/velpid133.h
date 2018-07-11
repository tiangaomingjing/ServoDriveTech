#ifndef VELPID133_H
#define VELPID133_H

#include <QWidget>

namespace Ui {
class VelPid133;
}
class QLabel;
class QDoubleSpinBox;

class VelPid133 : public QWidget
{
  Q_OBJECT

public:
  explicit VelPid133(QWidget *parent = 0);
  ~VelPid133();

  QDoubleSpinBox *boxP1();
  QDoubleSpinBox *boxI1();
  QDoubleSpinBox *boxP2();
  QDoubleSpinBox *boxI2();
  QDoubleSpinBox *boxTime();
  QDoubleSpinBox *boxSpdu();
  QDoubleSpinBox *boxSpdl();


  void setCurrentPidSegment(int index);

private slots:
  void onComboBoxIndexChanged(int index);
  void onBtnConfigHelpClicked();

signals:
  void comboBoxIndexChanged(int index);

private:
  void setPidSegmentUi(int index);

private:
  Ui::VelPid133 *ui;
  QLabel *m_helpPic;

};

#endif // VELPID133_H
