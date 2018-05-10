#ifndef IPLOTUNIT_H
#define IPLOTUNIT_H

#include <QWidget>
#include "iplotunit_global.h"


class IUiWidget;
class IPlotUnitPrivate;
class SevDevice;
/**
 * @brief The IPlotUnit class
 * 设计这个抽象接口类导出模块，是为了解决与UiPlot.dll的环形依赖
 * UiPlot->IPlotUint   PlotGraph-> (IPlotUint UiPlot)
 */
class IPLOTUNITSHARED_EXPORT IPlotUnit: public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IPlotUnit)
public:
  virtual ~IPlotUnit();
  virtual void visit(IUiWidget*uiWidget) = 0;
  virtual void respondUiActive(bool actived) = 0;
  void setSevDeviceList(const QList<SevDevice*> &sevlist);

signals:
  void winFloatingChange(bool isFloatIn);

protected:
  void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

public slots:
  virtual void onSevDeviceListChanged(const QList<SevDevice*> &sevlist) = 0;
  virtual void onAppClosed() = 0;
  virtual void onSocketConnectionChanged(bool isConnected) = 0;
protected:
  IPlotUnit(IPlotUnitPrivate&dd,QWidget *parent=0);
  IPlotUnitPrivate *d_ptr;
};

#endif // IPLOTUNIT_H
