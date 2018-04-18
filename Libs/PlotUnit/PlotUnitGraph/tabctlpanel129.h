#ifndef TABCTLPANEL129_H
#define TABCTLPANEL129_H

#include <QWidget>
#include "plottabctlprms.h"

namespace Ui {
class TabCtlPanel129;
}
class PlotUnitGraph129;
class SevDevice;

class TabCtlPanel129 : public QWidget
{
  Q_OBJECT
public:
  explicit TabCtlPanel129(SevDevice *sev,QWidget *parent = 0);
  ~TabCtlPanel129();

  void setupIcons(const QString &css);

signals:

public slots:
protected:
  bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

private slots:
  void onModeCtlPanelCheckChanged(quint16 axis,int mode);
  void onModeCtlPanelModeChanged(quint16 axis,int mode);
  void onCheckBoxCircleSWClicked();

private:
  friend class PlotUnitGraph129;
  Ui::TabCtlPanel129 *ui;
  SevDevice *m_sev;
  PlotTabCtlPrms *m_data;
};

#endif // TABCTLPANEL129_H
