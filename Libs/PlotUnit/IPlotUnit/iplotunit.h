#ifndef IPLOTUNIT_H
#define IPLOTUNIT_H

#include <QWidget>
#include "iplotunit_global.h"


class IUiWidget;
class IPlotUnitPrivate;
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

signals:
  void winFloatingChange(bool isFloatIn);

protected:
  void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

public slots:

protected:
  IPlotUnit(IPlotUnitPrivate&dd,QWidget *parent=0);
  IPlotUnitPrivate *d_ptr;
};

#endif // IPLOTUNIT_H
