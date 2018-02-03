#ifndef UISTATUS_H
#define UISTATUS_H

#include "uistatus_global.h"
#include "iuiwidget.h"

namespace Ui {
class UiStatus;
}

class QWidget;
class UiStatusPrivate;

class UISTATUSSHARED_EXPORT UiStatus:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiStatus)
public:
  explicit UiStatus(QWidget *parent = 0);
  ~UiStatus();

  void accept(QWidget*w) Q_DECL_OVERRIDE;

private:
  QStackedWidget *getUiStackedWidget(void)Q_DECL_OVERRIDE;
  QVBoxLayout *getVBoxLayout(void)Q_DECL_OVERRIDE;
  void setDefaultUi()Q_DECL_OVERRIDE;
  bool readPageFLASH()Q_DECL_OVERRIDE{return true;}
  bool writePageFLASH()Q_DECL_OVERRIDE{return true;}
  void setQmlContext()Q_DECL_OVERRIDE;
  void setQmlSignalSlot()Q_DECL_OVERRIDE;
  void addQmlWidget()Q_DECL_OVERRIDE;

private:
  Ui::UiStatus *ui;
};

#endif // UISTATUS_H
