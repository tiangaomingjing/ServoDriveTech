#ifndef UIMOTOR_H
#define UIMOTOR_H

#include "uimotor_global.h"
#include "iuiwidget.h"

namespace Ui {
class UiMotor;
}
class QWidget;
class UiMotorPrivate;

class UIMOTORSHARED_EXPORT UiMotor:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiMotor)
public:
  explicit UiMotor(QWidget *parent = 0);
  ~UiMotor();
private:
  Ui::UiMotor *ui;
};

#endif // UIMOTOR_H
