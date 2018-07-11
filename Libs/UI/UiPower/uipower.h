﻿#ifndef UIPOWER_H
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

  void accept(QWidget*w) Q_DECL_OVERRIDE;
  void setUiActive(bool actived)Q_DECL_OVERRIDE;
  bool writePageFLASH()Q_DECL_OVERRIDE;
  bool hasConfigFunc()Q_DECL_OVERRIDE;
  bool hasSaveFunc()Q_DECL_OVERRIDE;

protected:
  void setContextAction() Q_DECL_OVERRIDE;

protected slots:
//  void onActionReadRAM() Q_DECL_OVERRIDE;
//  void onActionReadFLASH() Q_DECL_OVERRIDE;

private:
  QStackedWidget *getUiStackedWidget(void)Q_DECL_OVERRIDE;
  QVBoxLayout *getVBoxLayout(void)Q_DECL_OVERRIDE;
  void setDefaultUi()Q_DECL_OVERRIDE;

private:
  Ui::UiPower *ui;
};

#endif // UIPOWER_H
