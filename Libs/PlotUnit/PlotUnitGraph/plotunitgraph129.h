#ifndef PLOTUNITGRAPH129_H
#define PLOTUNITGRAPH129_H

#include <QWidget>
#include "iplotunitgraph.h"
#include "plotunitgraph_global.h"

namespace Ui {
class PlotUnitGraph129;
}
class PlotUnitGraph129Private;
class QCustomPlot;

class PLOTUNITGRAPHSHARED_EXPORT PlotUnitGraph129 : public IPlotUnitGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(PlotUnitGraph129)

public:
  explicit PlotUnitGraph129(const QList<SevDevice *> &sevList,QWidget *parent = 0);
  ~PlotUnitGraph129();

  void respondUiActive(bool actived) Q_DECL_OVERRIDE;

public slots:
  void onSevDeviceListChanged(const QList<SevDevice *> &sevlist) Q_DECL_OVERRIDE;

private slots:
//  void onPushButtonTestClicked(bool checked);
  void onBtnFloatInClicked(bool checked);
  void onOptFaceCssChanged(const QString &css);

  void onBtnMeaHClicked(bool checked);
  void onBtnMeaVClicked(bool checked);
  void onBtnFitClicked();
  void onBtnConfigClicked();
  void onPlotPosHoverChanged(const QPointF &point);
  void onPlotMeaVposChanged(qreal v1, qreal v2, qreal dv);
  void onPlotMeaHposChanged(qreal v1, qreal v2, qreal dv);

  void onTimeOut();

  void onModeCtlPanelCheckChanged(quint16 axis,int mode);
  void onModeCtlPanelModeChanged(quint16 axis,int mode);

private:
  void createConnections();
  void setPlotIcons(const QString &css);
  void gtPlotInit();
  void ctlPanelInit();

  void setupSimpleDemo(QCustomPlot *customPlot);//test
  void setTimerStatus();

private:
  Ui::PlotUnitGraph129 *ui;
};

#endif // PLOTUNITGRAPH129_H
