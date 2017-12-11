#ifndef UIVELOCITY_H
#define UIVELOCITY_H

#include "uivelocity_global.h"
#include "iuiwidget.h"

namespace Ui {
class UiVelocity;
}
class QWidget;
class UiVelocityPrivate;

class UIVELOCITYSHARED_EXPORT UiVelocity:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiVelocity)
public:
  explicit UiVelocity(QWidget *parent = 0);
  ~UiVelocity();

  QStackedWidget *getUiStackedWidget(void)Q_DECL_OVERRIDE;

private:
  Ui::UiVelocity *ui;
};

#endif // UIVELOCITY_H
