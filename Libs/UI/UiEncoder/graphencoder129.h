#ifndef GRAPHENCODER129_H
#define GRAPHENCODER129_H

#include <QWidget>
#include "igraphencoder.h"
#include "uiencoder_global.h"

namespace Ui {
class GraphEncoder129;
}
class GraphEncoder129Private;

class UIENCODERSHARED_EXPORT GraphEncoder129 : public IGraphEncoder
{
  Q_OBJECT

  Q_DECLARE_PRIVATE(GraphEncoder129)
public:
  explicit GraphEncoder129(QWidget *parent = 0);
  ~GraphEncoder129();

private:
  Ui::GraphEncoder129 *ui;
};

#endif // GRAPHENCODER129_H
