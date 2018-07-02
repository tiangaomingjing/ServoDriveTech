#ifndef TABMODECTL_H
#define TABMODECTL_H

#include <QWidget>
#include "itabwidget.h"

namespace Ui {
class TabModeCtl;
}
class SevDevice;
class ModeCtlPrms;

class TabModeCtl : public ITabWidget
{
  Q_OBJECT

public:
  explicit TabModeCtl(const QString &name, SevDevice *sev, QWidget *parent = 0);
  ~TabModeCtl();

  void uiUpdate() Q_DECL_OVERRIDE;
  void resetUi() Q_DECL_OVERRIDE;

protected:
  bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
signals:

private slots:
  void onCssChanged(const QString &css);
  void onModeSpinBoxValueChanged(int value);
  void onModeCtlPanelModeChanged(quint16 axis, int mode);
  void onModeCtlPanelCheckChanged(quint16 axis, int mode);
  void onBtnServoOnClicked(bool checked); 

private:
  void setupIcons(const QString &css);
private:
  Ui::TabModeCtl *ui;
  int m_currenAxis;
  QList<ModeCtlPrms *>m_dataList;

};

#endif // TABMODECTL_H
