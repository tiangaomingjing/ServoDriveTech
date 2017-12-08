#ifndef UICURRENT_H
#define UICURRENT_H

#include "uicurrent_global.h"

#include "iuiwidget.h"

namespace Ui {
class UiCurrent;
}
class QWidget;
class UiCurrentPrivate;
class UICURRENTSHARED_EXPORT UiCurrent:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiCurrent)
public:
  explicit UiCurrent(QWidget *parent = 0);
  ~UiCurrent();
private:
  Ui::UiCurrent *ui;
};

#endif // UICURRENT_H
