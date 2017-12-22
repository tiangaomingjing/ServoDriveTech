#ifndef OPTPLOT_H
#define OPTPLOT_H

#include <QObject>
#include "iopt.h"

namespace Ui {
class OptPlot;
}
class OptPlotPrivate;

class OptPlot : public IOpt
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(OptPlot)
public:
  explicit OptPlot(const QString &optName, QWidget *parent = 0);
  ~OptPlot();
  bool optActive();

signals:

public slots:
private:
  Ui::OptPlot *ui;
};

#endif // OPTPLOT_H
