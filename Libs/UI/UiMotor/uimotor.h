﻿#ifndef UIMOTOR_H
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

  void accept(QWidget*w) Q_DECL_OVERRIDE;

private:
  QStackedWidget *getUiStackedWidget(void)Q_DECL_OVERRIDE;
  QVBoxLayout *getVBoxLayout(void)Q_DECL_OVERRIDE;
  void setDefaultUi()Q_DECL_OVERRIDE;
  void setQmlContext()Q_DECL_OVERRIDE;
  void setQmlSignalSlot()Q_DECL_OVERRIDE;
  void addQmlWidget()Q_DECL_OVERRIDE;
  void updateUi();
private:
  Ui::UiMotor *ui;
};

#endif // UIMOTOR_H
