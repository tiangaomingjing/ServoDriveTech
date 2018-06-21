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
  virtual ~GraphCurrent133();

protected slots:
  void onUIFItemClicked();

protected:
  void setCustomVisitActive(IUiWidget *uiWidget) Q_DECL_OVERRIDE;
  void setUiVersionName() Q_DECL_OVERRIDE;
  void setupDataMappings() Q_DECL_OVERRIDE;
  void createPidControllerItem() Q_DECL_OVERRIDE;

private slots:
  void onIIRFilterConfigClicked();
  void onIIRFilterSaveClicked();

};

#endif // GRAPHCURRENT129_H
