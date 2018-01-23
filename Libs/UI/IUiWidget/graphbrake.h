#ifndef GRAPHBRAKE_H
#define GRAPHBRAKE_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraph.h"

class GraphBrakePrivate;
class IUiWidget;
class IUIWIDGETSHARED_EXPORT GraphBrake : public IGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphBrake)
public:
  explicit GraphBrake(QWidget *parent = 0);
  virtual ~GraphBrake();
  virtual void visit(IUiWidget*ui)=0;

signals:

public slots:
protected:
  GraphBrake(GraphBrakePrivate&d, QWidget *parent=0);
};

#endif // IGRAPHBRAKE_H
