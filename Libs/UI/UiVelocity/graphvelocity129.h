#ifndef GRAPHVELOCITY129_H
#define GRAPHVELOCITY129_H

#include <QWidget>
#include "uivelocity_global.h"
#include "igraphvelocity.h"

namespace Ui {
class GraphVelocity129;
}
class GraphVelocity129Private;

class UIVELOCITYSHARED_EXPORT GraphVelocity129 : public IGraphVelocity
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphVelocity129)
public:
  explicit GraphVelocity129(QWidget *parent = 0);
  ~GraphVelocity129();

protected:
  void setCustomVisitActive(IUiWidget *uiWidget) Q_DECL_OVERRIDE;
  void setUiVersionName() Q_DECL_OVERRIDE;
  void setupDataMappings() Q_DECL_OVERRIDE;

private:
  Ui::GraphVelocity129 *ui;
};

#endif // GRAPHVELOCITY129_H
