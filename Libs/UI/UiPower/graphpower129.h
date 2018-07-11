﻿#ifndef GRAPHPOWER129_H
#define GRAPHPOWER129_H

#include <QWidget>
#include "igraphpower.h"
#include "uipower_global.h"

class QDoubleSpinBox;
class QTreeWidgetItem;

namespace Ui {
class GraphPower129;
}
class GraphPower129Private;

class UIPOWERSHARED_EXPORT GraphPower129 : public IGraphPower
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphPower129)
public:
  explicit GraphPower129(QWidget *parent = 0);
  ~GraphPower129();

   void syncTreeDataToUiFace() Q_DECL_OVERRIDE;

protected:
  void setCustomVisitActive(IUiWidget *uiWidget) Q_DECL_OVERRIDE;
  void setUiVersionName() Q_DECL_OVERRIDE;
  void setupDataMappings() Q_DECL_OVERRIDE;

private:
  Ui::GraphPower129 *ui;

};

#endif // GRAPHPOWER129_H
