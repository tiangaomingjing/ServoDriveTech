#ifndef GRAPHBRAKE129_H
#define GRAPHBRAKE129_H

#include <QWidget>
#include "igraphbrake.h"
#include "uibrake_global.h"

namespace Ui {
class GraphBrake129;
}
class GraphBrake129Private;
class UIBRAKESHARED_EXPORT GraphBrake129 : public IGraphBrake
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphBrake129)
public:
  explicit GraphBrake129(QWidget *parent = 0);
  ~GraphBrake129();

signals:

public slots:
private:
  Ui::GraphBrake129 *ui;
};

#endif // GRAPHBRAKE129_H
