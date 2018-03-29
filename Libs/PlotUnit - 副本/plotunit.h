#ifndef PLOTUNIT_H
#define PLOTUNIT_H

#include "plotunit_global.h"
#include <QWidget>
class PlotUnitPrivate;
namespace Ui {
class PlotUnit;
}
class PLOTUNITSHARED_EXPORT PlotUnit:public QWidget
{
  Q_OBJECT
public:
  explicit PlotUnit(QWidget *parent = 0);
  ~PlotUnit();
signals:
  void floatingChanged(bool floating);
private slots:
  void on_pushButton_clicked();

private:
  Ui::PlotUnit *ui;
  PlotUnitPrivate *d;
};

#endif // PLOTUNIT_H
