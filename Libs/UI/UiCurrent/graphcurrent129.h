#ifndef GRAPHCURRENT129_H
#define GRAPHCURRENT129_H

#include <QWidget>
#include "igraphcurrent.h"
#include "uicurrent_global.h"

namespace Ui {
class GraphCurrent129;
}
class GraphCurrent129Private;

class UICURRENTSHARED_EXPORT GraphCurrent129 : public IGraphCurrent
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphCurrent129)
public:
  explicit GraphCurrent129(QWidget *parent = 0);
  ~GraphCurrent129();

protected:
  void setCustomVisitActive(IUiWidget *uiWidget) Q_DECL_OVERRIDE;
  void setUiVersionName() Q_DECL_OVERRIDE;
  void setupDataMappings() Q_DECL_OVERRIDE;

private:
  Ui::GraphCurrent129 *ui;
};

#endif // GRAPHCURRENT129_H
