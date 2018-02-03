#ifndef UIRAM_H
#define UIRAM_H

#include "uiram_global.h"
#include "iuiwidget.h"

namespace Ui {
class UiRAM;
}
class QWidget;
class UiRAMPrivate;

class UIRAMSHARED_EXPORT UiRAM:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiRAM)
public:
  explicit UiRAM(QWidget *parent = 0);
  ~UiRAM();

  bool readPageFLASH()Q_DECL_OVERRIDE{return true;}
  bool writePageFLASH()Q_DECL_OVERRIDE{return true;}
  void createQmlWidget()Q_DECL_OVERRIDE{}
private:
  QStackedWidget *getUiStackedWidget(void) Q_DECL_OVERRIDE;
  QVBoxLayout *getVBoxLayout(void)Q_DECL_OVERRIDE;
  void setDefaultUi()Q_DECL_OVERRIDE;

private:
  Ui::UiRAM *ui;
};

#endif // UIRAM_H
