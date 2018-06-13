#ifndef GRAPHCURRENT133_H
#define GRAPHCURRENT133_H

#include <QWidget>
#include "igraphcurrent.h"
#include "uicurrent_global.h"

class GraphCurrent133Private;

class UICURRENTSHARED_EXPORT GraphCurrent133 : public IGraphCurrent
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphCurrent133)
public:
  explicit GraphCurrent133(QWidget *parent = 0);
  ~GraphCurrent133();

protected:
  void setCustomVisitActive(IUiWidget *uiWidget) Q_DECL_OVERRIDE;
  void setUiVersionName() Q_DECL_OVERRIDE;
  void setupDataMappings() Q_DECL_OVERRIDE;

  void createPidControllerItem() Q_DECL_OVERRIDE;
};

#endif // GRAPHCURRENT129_H
