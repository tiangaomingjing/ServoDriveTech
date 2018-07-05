#ifndef NOLINEARCONTROLLER133_H
#define NOLINEARCONTROLLER133_H

#include <QObject>
class QGraphicsView;
class QRadioButton;
class NodeBlock;
class QGraphicsItem;
class QDoubleSpinBox;
class KuSelectWidget133;
class NodePort;
class NodeSwitch;
class BoxItemMapping;
class INodeConnection;
class QPushButton;
class QProgressBar;

class NolinearController133 : public QObject
{
  Q_OBJECT
public:
  explicit NolinearController133(QGraphicsView *view,QObject *parent = 0);
  ~NolinearController133();

  void adjustPostion();
  void setPos(const QPointF &p);
  void setPos(qreal x,qreal y);

  QDoubleSpinBox *boxAcc();
  QDoubleSpinBox *boxKd();
  QDoubleSpinBox *boxKi();
  QDoubleSpinBox *boxKp();
  QDoubleSpinBox *boxKn();
  QDoubleSpinBox *boxFn();
  QDoubleSpinBox *boxQx();
  QDoubleSpinBox *boxKavToPeer();
  QDoubleSpinBox *boxKu1();
  QDoubleSpinBox *boxKu2();
  QDoubleSpinBox *boxTs();
  QDoubleSpinBox *boxSpdu();
  QDoubleSpinBox *boxSpdl();
  QDoubleSpinBox *boxSatnAbs();
  QDoubleSpinBox *boxSatnPos();
  QDoubleSpinBox *boxSatnNeg();
  QDoubleSpinBox *boxMotionAcc();
  QDoubleSpinBox *boxMotionDec();
  QDoubleSpinBox *boxMotionMaxSpd();
  QDoubleSpinBox *boxMotionPos();

  void setDir(int dir);
  void setCurrentKuMode(int mode);
  void setSwON(bool on);
  BoxItemMapping *boxItemMapping() const;

  void setBtnAutoTurningUiOn(bool on);
  void setAutoTurningProgressBarValue(int v);


signals:
  void dirChanged(int dir);
  void inputFilterItemClicked();
  void kuSelectChanged(int index);
  void swChanged(bool isOn);
  void btnAutoStartClicked(bool checked);

private slots:
  void onRadioBtnClicked();
  void onSaturationClicked(bool checked);
  void onBtnAutoStartClicked(bool checked);
private:
  void createDirItem();
  void createInputFilterItem();
  void createCurrentItem();
  void createAccItem();
  void createKdItem();
  void createKpItem();
  void createKiItem();
  void createKnItem();
  void createKuSelItem();
  void createStartItem();
  void createEndItem();
  void createSumItem();
  void createMidPortItem();
  void createSwitchItem();
  void createANVSFreqItem();
  void createANVSGainItem();
  void createFeedBackItem();
  void createSaturationItem();
  void createSaturationConfigItem();
  void createAutoTurningItem();

  void createArrowsItem();

  void resetAllItemParent();

  void addItem(QGraphicsItem *item);
private:
  QGraphicsView *m_view;

  NodeBlock *m_dirItem;
  QRadioButton *m_cwRBtn;
  QRadioButton *m_ccwRBtn;

  NodeBlock *m_inputFilterItem;

  NodeBlock *m_currentCtlerItem;

  NodeBlock *m_accItem;
  QDoubleSpinBox *m_boxAcc;

  NodeBlock *m_saturationItem;

  NodeBlock *m_kdItem;
  QDoubleSpinBox *m_boxKd;
  NodeBlock *m_kpItem;
  QDoubleSpinBox *m_boxKp;
  NodeBlock *m_kiItem;
  QDoubleSpinBox *m_boxKi;
  NodeBlock *m_knItem;
  QDoubleSpinBox *m_boxKn;

  NodeBlock *m_kuSelectItem;
  KuSelectWidget133 *m_kuSelectWidget;

  NodePort *m_startPort;
  NodePort *m_endPort;
  NodePort *m_midPort1;
  NodePort *m_midPort2;
  NodePort *m_midPort3;
  NodePort *m_midPort4;
  NodePort *m_midPortFB;
  NodePort *m_midPortNULL;

  NodeBlock *m_sum1Item;
  NodeBlock *m_sum2Item;

  NodeSwitch *m_swItem;

  NodeBlock *m_anvsKgItem;
  QDoubleSpinBox *m_boxANVSKg;

  NodeBlock *m_anvsFreqItem;
  QDoubleSpinBox *m_boxANVSFn;
  QDoubleSpinBox *m_boxANVSQx;

  NodeBlock *m_posFBItem;

  //饱和框
  NodeBlock *m_satnFrame;
  NodeBlock *m_satnAbs;
  NodeBlock *m_satnPos;
  NodeBlock *m_satnNeg;
  QDoubleSpinBox *m_boxSatnAbs;
  QDoubleSpinBox *m_boxSatnPos;
  QDoubleSpinBox *m_boxSatnNeg;
  QList<INodeConnection *>m_nodeConnectionList;

  BoxItemMapping *m_boxItemMapping;

  NodeBlock      *m_autoTnItem;
  QDoubleSpinBox *m_boxAutoTnAcc;
  QDoubleSpinBox *m_boxAutoTnDec;
  QDoubleSpinBox *m_boxAutoTnMaxVel;
  QDoubleSpinBox *m_boxAutoTnPulseNum;
  QPushButton    *m_btnAutoStart;
  QProgressBar   *m_bar;

};

#endif // NOLINEARCONTROLLER133_H
