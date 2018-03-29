#ifndef PLOTUNITGRAPH129_H
#define PLOTUNITGRAPH129_H

#include <QWidget>
#include "iplotunitgraph.h"
#include "plotunitgraph_global.h"

namespace Ui {
class PlotUnitGraph129;
}
class PlotUnitGraph129Private;

class PLOTUNITGRAPHSHARED_EXPORT PlotUnitGraph129 : public IPlotUnitGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(PlotUnitGraph129)

public:
  explicit PlotUnitGraph129(QWidget *parent = 0);
  ~PlotUnitGraph129();

private slots:
  void onPushButtonTestClicked(bool checked);

private:
  Ui::PlotUnitGraph129 *ui;
};

#endif // PLOTUNITGRAPH129_H
