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
  void onBtnMotionGoClicked(bool checked);

private:
  void setupIcons(const QString &css);
  void setUiCurrentCtlSrc(int src);
private:
  Ui::TabMotion *ui;
  int m_currentAxis;
  QList<TabMotionData * >m_axisMotionDataList;//保存各个轴设置的运动模式，用于点击还原界面
  QList<IMotion *>m_motionList;
};

#endif // TABMOTION_H
