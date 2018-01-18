#ifndef GRAPHSTATUS129_H
#define GRAPHSTATUS129_H

#include <QWidget>
#include "igraphstatus.h"
#include "uistatus_global.h"

namespace Ui {
class GraphStatus129;
}
class GraphStatus129Private;
class UISTATUSSHARED_EXPORT GraphStatus129 : public IGraphStatus
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphStatus129)
public:
  explicit GraphStatus129(QWidget *parent = 0);
  ~GraphStatus129();

private:
  Ui::GraphStatus129 *ui;
};

#endif // GRAPHSTATUS129_H
