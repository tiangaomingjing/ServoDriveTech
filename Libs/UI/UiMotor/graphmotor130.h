#ifndef GRAPHMOTOR130_H
#define GRAPHMOTOR130_H

#include <QWidget>
#include "uimotor_global.h"
#include "igraphmotor.h"
#include "optface.h"

namespace Ui {
class GraphMotor130;
}
class GraphMotor130Private;
class QDoubleSpinBox;
class QTreeWidgetItem;
class UIMOTORSHARED_EXPORT GraphMotor130 : public IGraphMotor
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphMotor130)
public:
  explicit GraphMotor130(QWidget *parent = 0);
  ~GraphMotor130();

  void syncTreeDataToUiFace() Q_DECL_OVERRIDE;

protected:
  void setCustomVisitActive(IUiWidget *uiWidget) Q_DECL_OVERRIDE;
  void setUiVersionName() Q_DECL_OVERRIDE;
  void setupDataMappings() Q_DECL_OVERRIDE;

protected slots:
  void onDoubleSpinBoxFocusOut();

private:
  Ui::GraphMotor130 *ui;
};

#endif // GRAPHMOTOR129_H
