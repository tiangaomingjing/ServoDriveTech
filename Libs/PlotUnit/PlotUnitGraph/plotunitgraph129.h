#ifndef PLOTUNITGRAPH129_H
#define PLOTUNITGRAPH129_H

#include <QWidget>
#include "iplotunitgraph.h"
#include "plotunitgraph_global.h"
#include "plotdata.h"

namespace Ui {
class PlotUnitGraph129;
}
class PlotUnitGraph129Private;
class QCustomPlot;
class QTreeWidgetItem;
class QTableWidget;
class ICurve;
class QTableWidgetItem;
class QCPGraph;
class OptPlot;

class PLOTUNITGRAPHSHARED_EXPORT PlotUnitGraph129 : public IPlotUnitGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(PlotUnitGraph129)
  Q_PROPERTY(QColor curveShowColor READ curveShowColor WRITE setCurveShowColor)
  Q_PROPERTY(QColor curveBackShowColor READ curveBackShowColor WRITE setCurveBackShowColor)
  Q_PROPERTY(QColor curveHideColor READ curveHideColor WRITE setCurveHideColor)
  Q_PROPERTY(QColor curveBackHideColor READ curveBackHideColor WRITE setCurveBackHideColor)

public:
  explicit PlotUnitGraph129(const QList<SevDevice *> &sevList,QWidget *parent = 0);
  ~PlotUnitGraph129();

  void respondUiActive(bool actived) Q_DECL_OVERRIDE;

  QColor curveShowColor() const ;
  void setCurveShowColor(const QColor &color);
  QColor curveBackShowColor() const;
  void setCurveBackShowColor(const QColor &color);
  QColor curveHideColor() const;
  void setCurveHideColor(const QColor &color);
  QColor curveBackHideColor() const;
  void setCurveBackHideColor(const QColor &color);

public slots:
  void onBeforeSevDeviceChanged() Q_DECL_OVERRIDE;
  void onSevDeviceListChanged(const QList<SevDevice *> &sevlist) Q_DECL_OVERRIDE;
  void onAppClosed() Q_DECL_OVERRIDE;
  void onSocketConnectionChanged(bool isConnected) Q_DECL_OVERRIDE;

private slots:
  void onBtnFloatInClicked(bool checked);
  void onOptFaceCssChanged(const QString &css);
  void onWinFloatingChanged(bool isFloating);

  void onBtnStartSampleClicked(bool checked);
  void onBtnMeaHClicked(bool checked);
  void onBtnMeaVClicked(bool checked);
  void onBtnFitClicked();
  void onBtnLoadAllCurveClicked();
  void onBtnOpenCurveClicked(bool checked);
  void onBtnSaveCurveClicked();
  void onPlotPosHoverChanged(const QPointF &point);
  void onPlotMeaVposChanged(qreal v1, qreal v2, qreal dv);
  void onPlotMeaHposChanged(qreal v1, qreal v2, qreal dv);

  void onTimeOut();
  void onListWidgetDeviceCurrentRowChanged(int row);

  //曲线相关
  void onBtnCurveAddClicked();
  void onExpertTreeWidgetDoubleClicked(QTableWidget *table,QTreeWidgetItem *item);
  void onAddUsrCurveRequested(ICurve *c);
  void onBtnCurveRemoveClicked();
  void onBtnCurveClearClicked();
  void onBtnCurveShowAllClicked();
  void onCurveTableItemClicked(QTableWidgetItem * item);
  void onCurveTableItemDoubleClicked(QTableWidgetItem * item);
  void onCurveTableItemEnteredMoreDetail(QTableWidgetItem * item);//鼠标悬停，可以显示详细的名称
  void onPlotDataIn(PlotData data);

  void onPlotSelectionRectFinish();

  void onMotionStart();
  void onMotionStop();

  void onDspReset() Q_DECL_OVERRIDE;

  void onPopupMenuAxisClicked();
  void onPlotCurveTablePopupMenuRequested(const QPoint &point);

private:
  void createConnections();
  void setPlotIcons(const QString &css);
  void gtPlotInit();
  void ctlPanelInit();
  void updateCtlPanelBySelectDevice(int sevInx);
  void resizeSectionCurveTableWidget(const QList<SevDevice *> &sevlist);

  void setupSimpleDemo(QCustomPlot *customPlot);//test
  void setTimerStatus();

  SevDevice *currentSevDevice() const;
  void addTableRowPrm(ICurve *curve , QCPGraph *graph);

  void clearGraphData();
  void checkCurveValid();

  void showAllData();

  OptPlot *optPlot(void);

  void initialCurvesFromXml();

  void setUiStatusSampling(bool en);
  void setUiStatusCurveTableWidgetOnOff(int row,bool on);

  void addPopupMenuActionAxis(quint8 axisMaxCount);

private:
  Ui::PlotUnitGraph129 *ui;

};

#endif // PLOTUNITGRAPH129_H
