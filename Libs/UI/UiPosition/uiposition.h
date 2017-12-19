#ifndef UIPOSITION_H
#define UIPOSITION_H

#include "uiposition_global.h"
#include "iuiwidget.h"

namespace Ui {
class UiPosition;
}

class QWidget;
class UiPositionPrivate;
class UIPOSITIONSHARED_EXPORT UiPosition:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiPosition)
public:
  explicit UiPosition(QWidget *parent = 0);
  ~UiPosition();
private:
    QStackedWidget *getUiStackedWidget(void)Q_DECL_OVERRIDE;
    QVBoxLayout *getVBoxLayout(void)Q_DECL_OVERRIDE;
    void setDefaultUi()Q_DECL_OVERRIDE;
    void setQmlContext()Q_DECL_OVERRIDE;
    void setQmlSignalSlot()Q_DECL_OVERRIDE;
    void addQmlWidget()Q_DECL_OVERRIDE;
private:
  Ui::UiPosition *ui;
};

#endif // UIPOSITION_H
