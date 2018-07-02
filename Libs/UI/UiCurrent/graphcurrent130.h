#ifndef GRAPHCURRENT130_H
#define GRAPHCURRENT130_H

#include <QWidget>
#include "igraphcurrent.h"
#include "uicurrent_global.h"

class GraphCurrent130Private;

class UICURRENTSHARED_EXPORT GraphCurrent130 : public IGraphCurrent
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphCurrent130)
public:
  explicit GraphCurrent130(QWidget *parent = 0);
  ~GraphCurrent130();

protected:
  void setCustomVisitActive(IUiWidget *uiWidget) Q_DECL_OVERRIDE;
  void setUiVersionName() Q_DECL_OVERRIDE;
  void setupDataMappings() Q_DECL_OVERRIDE;

  void createPidControllerItem() Q_DECL_OVERRIDE;
  QPointF pidInitPos() Q_DECL_OVERRIDE;
};

#endif // GRAPHCURRENT129_H
