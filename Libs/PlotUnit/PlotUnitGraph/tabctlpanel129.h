#ifndef TABCTLPANEL129_H
#define TABCTLPANEL129_H

#include <QWidget>
#include "plottabctlprms.h"

namespace Ui {
class TabCtlPanel129;
}
class PlotUnitGraph129;
class SevDevice;
class ITabWidget;

class TabCtlPanel129 : public QWidget
{
  Q_OBJECT
public:
  explicit TabCtlPanel129(SevDevice *sev,QWidget *parent = 0);
  ~TabCtlPanel129();

  void updateServoStatus();

signals:

public slots:
private slots:
  void onTabCurrentChanged(int inx);

private:
  friend class PlotUnitGraph129;
  Ui::TabCtlPanel129 *ui;
  SevDevice *m_sev;
  int m_currentTabInx;
  QList<ITabWidget *>m_tabWidgetList;
};

#endif // TABCTLPANEL129_H
