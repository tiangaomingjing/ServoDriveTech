#ifndef POSPID133_H
#define POSPID133_H

#include <QWidget>

namespace Ui {
class PosPID133;
}

class QDoubleSpinBox;
class QPushButton;
class QLabel;

class PosPID133 : public QWidget
{
  Q_OBJECT

public:
  explicit PosPID133(QWidget *parent = 0);
  ~PosPID133();
  QDoubleSpinBox *boxFirstFn();
  QDoubleSpinBox *boxSecondFn();
  QDoubleSpinBox *boxTransTime();
  QDoubleSpinBox *boxSpdUp();
  QDoubleSpinBox *boxSpdLow();
  int currentPidSegmentIndex();
  void setCurrentPidSegment(int index);

private slots:
  void onComboBoxIndexChanged(int index);
  void onBtnConfigHelpClicked();

signals:
  void comboBoxIndexChanged(int index);
  void pidTitleClicked();

private:
  Ui::PosPID133 *ui;
  QPushButton *m_btnHelp;
  QLabel *m_helpPic;
};

#endif // POSPID133_H
