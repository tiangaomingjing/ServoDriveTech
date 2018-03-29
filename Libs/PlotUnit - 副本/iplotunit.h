#ifndef IPLOTUNIT_H
#define IPLOTUNIT_H

#include <QWidget>
#include "plotunit_global.h"

class IUiWidget;
class IPlotUnitPrivate;

class PLOTUNITSHARED_EXPORT IPlotUnit : public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IPlotUnit)
public:

  virtual ~IPlotUnit();
  virtual void visit(IUiWidget*uiWidget);

signals:
  void winFloatingChange(bool isFloatIn);

public slots:

protected:
  IPlotUnit(IPlotUnitPrivate&dd,QWidget *parent=0);
  IPlotUnitPrivate *d_ptr;
};

#endif // IPLOTUNIT_H
