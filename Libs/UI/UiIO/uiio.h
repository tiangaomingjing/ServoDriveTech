#ifndef UIIO_H
#define UIIO_H

#include "uiio_global.h"
#include "iuiwidget.h"

namespace Ui {
class UiIO;
}
class QWidget;
class UiIOPrivate;

class UIIOSHARED_EXPORT UiIO:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiIO)
public:
  explicit UiIO(QWidget *parent = 0);
  ~UiIO();

  bool readPageFLASH()Q_DECL_OVERRIDE{return true;}
  bool writePageFLASH()Q_DECL_OVERRIDE{return true;}

  void accept(QWidget*w) Q_DECL_OVERRIDE;

  bool hasConfigFunc() {return false;}
  bool hasSaveFunc() {return false;}

private:
  QStackedWidget *getUiStackedWidget(void)Q_DECL_OVERRIDE;
  QVBoxLayout *getVBoxLayout(void)Q_DECL_OVERRIDE;
  void setDefaultUi()Q_DECL_OVERRIDE;

private:
  Ui::UiIO *ui;
};

#endif // UIIO_H
