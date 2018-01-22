#ifndef GRAPHMOTOR129_H
#define GRAPHMOTOR129_H

#include <QWidget>
#include "uimotor_global.h"
#include "igraphmotor.h"

namespace Ui {
class GraphMotor129;
}
class GraphMotor129Private;
class UIMOTORSHARED_EXPORT GraphMotor129 : public IGraphMotor
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphMotor129)
public:
  explicit GraphMotor129(QWidget *parent = 0);
  ~GraphMotor129();
  void accept(IUiWidget *ui)Q_DECL_OVERRIDE;
protected:
  bool eventFilter(QObject *obj, QEvent *event);

private:
  Ui::GraphMotor129 *ui;
};

#endif // GRAPHMOTOR129_H
