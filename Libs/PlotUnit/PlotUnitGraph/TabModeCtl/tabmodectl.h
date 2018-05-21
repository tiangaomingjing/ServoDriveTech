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
  explicit TabModeCtl(const QString &name,int axisCount ,SevDevice *sev,QWidget *parent = 0);
  ~TabModeCtl();

  void setupIcons(const QString &css);

protected:
  bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
private slots:
  void onCssChanged(const QString &css);
  void onModeSpinBoxValueChanged(int value);
  void onModeCtlPanelModeChanged(quint16 axis, int mode);
  void onModeCtlPanelCheckChanged(quint16 axis, int mode);

private:
  Ui::TabModeCtl *ui;
  int m_currenAxis;
  QList<ModeCtlPrms *>m_prms;

};

#endif // TABMODECTL_H
