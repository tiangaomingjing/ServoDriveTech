#ifndef TABMOTION_H
#define TABMOTION_H

#include <QWidget>
#include "itabwidget.h"
#include "sdtglobaldef.h"

namespace Ui {
class TabMotion;
}
class IMotion;
class QListWidgetItem;


class TabMotionData
{
public:
  TabMotionData():
    m_ctlSrc(GT::SEV_CTL_SRC_GLINK2),
    m_curMotion(NULL)
  {

  }
  ~TabMotionData()
  {

  }
  GT::SevControlSrc m_ctlSrc;
  IMotion *m_curMotion;
};

class QProgressBar;
class MotionProgressBar :public QWidget
{
  Q_OBJECT
public:
  explicit MotionProgressBar(int axisCount ,QWidget *parent  = 0);
  ~MotionProgressBar();

  void hideAllBar();
  void resetAllBarValue();
  void setBarValue(int axisInx,int value);

private:
  int m_axisCount;
  QList<QProgressBar *>m_barList;
};

class TabMotion : public ITabWidget
{
  Q_OBJECT

public:
  explicit TabMotion(const QString &name, SevDevice *sev, QWidget *parent = 0);
  ~TabMotion();

  void uiUpdate() Q_DECL_OVERRIDE;
  void resetUi() Q_DECL_OVERRIDE;

private slots:
  void onCssChanged(const QString &css);
  void onMotionAxisRowChanged(int row);
  void onBtnCtlSrcPcClicked();
  void onBtnCtlSrcGLink2Clicked();
  void onListWidgetMotionTypeInxClicked(QListWidgetItem *item);
  void onBtnServoOnClicked(bool checked);
  void onBtnMotionGoClicked(bool checked);
  void onProgressValueChanged(quint16 axisInx,int value);
  void onMotionAllDone();

signals:

private:
  void setupIcons(const QString &css);
  void setUiCurrentCtlSrc(int src);
private:
  Ui::TabMotion *ui;
  int m_currentAxis;
  QList<TabMotionData * >m_axisMotionDataList;//保存各个轴设置的运动模式，用于点击还原界面
  QList<IMotion *>m_motionList;
  MotionProgressBar *m_barWidget;
};

#endif // TABMOTION_H
