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

  void accept(QWidget*w) Q_DECL_OVERRIDE;
  void setUiActive(bool actived)Q_DECL_OVERRIDE;

private:
  QStackedWidget *getUiStackedWidget(void)Q_DECL_OVERRIDE;
  QVBoxLayout *getVBoxLayout(void)Q_DECL_OVERRIDE;
  void setDefaultUi()Q_DECL_OVERRIDE;
  void setQmlContext()Q_DECL_OVERRIDE;
  void setQmlSignalSlot()Q_DECL_OVERRIDE;
  void addQmlWidget()Q_DECL_OVERRIDE;
private:
  Ui::UiCurrent *ui;
};

#endif // UICURRENT_H
