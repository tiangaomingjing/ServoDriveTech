#ifndef IIRFILTER_H
#define IIRFILTER_H

#include <QWidget>

namespace Ui {
class IIRFilter;
}
class NodePort;
class NodeSwitch;
class NodeBlock;
class INodeConnection;
class QComboBox;
class QDoubleSpinBox;

class IIRFilter : public QWidget
{
  Q_OBJECT

public:
  explicit IIRFilter(QWidget *parent = 0);
  ~IIRFilter();

  void updatePos();

  QDoubleSpinBox *boxFn1();
  QDoubleSpinBox *boxFn2();
  QDoubleSpinBox *boxQx2();
  QDoubleSpinBox *boxFnNch();
  QDoubleSpinBox *boxQxNch();
  QDoubleSpinBox *boxKnNch();
  int currentFitSelectIndex();
  void setFitSelectIndex(int index);

signals:
  void fitSelectChanged(int index);
  void configClicked();
  void saveClicked();

private slots:
  void onComboxIndexChanged(int index);
  void onSwitchClicked(bool isOn);
  void onBtnExitClicked();

private:
  Ui::IIRFilter *ui;

  NodePort *m_p1;
  NodePort *m_p2;
  NodePort *m_p3;
  NodeSwitch *m_s1;
  NodeBlock *m_u1;
  INodeConnection *m_l1;
  INodeConnection *m_l2;
  INodeConnection *m_l3;
  INodeConnection *m_l4;
  INodeConnection *m_l5;
  QComboBox *m_comboBox;

};

#endif // IIRFILTER_H
