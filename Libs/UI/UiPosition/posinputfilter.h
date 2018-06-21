#ifndef POSINPUTFILTER_H
#define POSINPUTFILTER_H

#include <QWidget>

namespace Ui {
class PosInputFilter;
}
class NodePort;
class NodeSwitch;
class NodeBlock;
class INodeConnection;
class QComboBox;
class QDoubleSpinBox;
class QDoubleSpinBox;

class PosInputFilter : public QWidget
{
  Q_OBJECT

public:
  explicit PosInputFilter(QWidget *parent = 0);
  ~PosInputFilter();

  void updatePos();

  QDoubleSpinBox *boxFn1();
  QDoubleSpinBox *boxFn2();
  QDoubleSpinBox *boxQx2();
  QDoubleSpinBox *boxFnNch();
  QDoubleSpinBox *boxQxNch();
  QDoubleSpinBox *boxKnNch();

  QDoubleSpinBox *boxMafNum();

  int currentIIRFilterIndex();
  void setIIRFilterIndex(int index);


  quint16 SW() const;
  void setSW(quint16 SW);

signals:
  void fitSelectChanged(int index);
  void configClicked();
  void saveClicked();

private slots:
  void onComboxIndexChanged(int index);
  void onSwitch1Clicked(bool isOn);
  void onSwitch2Clicked(bool isOn);
  void onBtnExitClicked();

private:
  Ui::PosInputFilter *ui;

  NodePort *m_p1;
  NodePort *m_p2;
  NodePort *m_p3;
  NodePort *m_p4;
  NodeSwitch *m_s1;
  NodeSwitch *m_s2;
  NodeBlock *m_u1;
  NodeBlock *m_u2;
  INodeConnection *m_l1;
  INodeConnection *m_l2;
  INodeConnection *m_l3;
  INodeConnection *m_l4;
  INodeConnection *m_l5;
  INodeConnection *m_l6;
  INodeConnection *m_l7;
  INodeConnection *m_l8;
  INodeConnection *m_l9;
  QComboBox *m_comboBox;
  QDoubleSpinBox *m_mafNum;
  quint16 m_SW;
};

#endif // POSINPUTFILTER_H
