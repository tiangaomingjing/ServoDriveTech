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
  explicit PlotUnitGraph129(QWidget *parent = 0);
  ~PlotUnitGraph129();

private slots:
//  void onPushButtonTestClicked(bool checked);
  void onBtnFloatInClicked(bool checked);
  void onOptFaceCssChanged(const QString &css);

  void onBtnMeaHClicked(bool checked);
  void onBtnMeaVClicked(bool checked);
  void onBtnFitClicked();
  void onPlotPosHoverChanged(const QPointF &point);
  void onPlotMeaVposChanged(qreal v1, qreal v2, qreal dv);
  void onPlotMeaHposChanged(qreal v1, qreal v2, qreal dv);

private:
  void createConnections();
  void setPlotIcons(const QString &css);
  void gtPlotInit();
  void ctlPanelInit();

  void setupSimpleDemo(QCustomPlot *customPlot);//test

private:
  Ui::PlotUnitGraph129 *ui;
};

#endif // PLOTUNITGRAPH129_H
