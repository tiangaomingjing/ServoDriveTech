#ifndef UIPOWER_H
#define UIPOWER_H

#include "uipower_global.h"
#include "iuiwidget.h"

namespace Ui {
class UiPower;
}
class QWidget;
class UiPowerPrivate;

class UIPOWERSHARED_EXPORT UiPower:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiPower)
public:
  explicit UiPower(QWidget *parent = 0);
  ~UiPower();
private:
  Ui::UiPower *ui;
};

#endif // UIPOWER_H
