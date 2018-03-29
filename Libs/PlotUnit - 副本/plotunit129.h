#ifndef PLOTUNIT129_H
#define PLOTUNIT129_H

#include <QWidget>
#include "iplotunit.h"

class PlotUnit129Private;

namespace Ui {
class PlotUnit129;
}

class PLOTUNITSHARED_EXPORT PlotUnit129 : public IPlotUnit
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(PlotUnit129)

public:
  explicit PlotUnit129(QWidget *parent = 0);
  ~PlotUnit129();

private:
  Ui::PlotUnit129 *ui;
};

#endif // PLOTUNIT129_H
