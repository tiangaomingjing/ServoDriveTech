#ifndef GRAPHBRAKE129_H
#define GRAPHBRAKE129_H

#include <QWidget>
#include "igraphbrake.h"
#include "uibrake_global.h"

namespace Ui {
class GraphBrake129;
}
class GraphBrake129Private;
class QDoubleSpinBox;
class QTreeWidgetItem;

class BrakePaintPrivate:public QWidget
{
  Q_OBJECT
public:
  explicit BrakePaintPrivate(QWidget *parent);
  ~BrakePaintPrivate();
protected:
  void paintEvent(QPaintEvent *event);

private:
};

class UIBRAKESHARED_EXPORT GraphBrake129 : public IGraphBrake
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphBrake129)
public:
  explicit GraphBrake129(QWidget *parent = 0);
  ~GraphBrake129();

  void syncTreeDataToUiFace() Q_DECL_OVERRIDE;

protected:
  void setCustomVisitActive(IUiWidget *uiWidget) Q_DECL_OVERRIDE;
  void setUiVersionName() Q_DECL_OVERRIDE;
  void setupDataMappings() Q_DECL_OVERRIDE;

private:
  Ui::GraphBrake129 *ui;
};

#endif // GRAPHBRAKE129_H
