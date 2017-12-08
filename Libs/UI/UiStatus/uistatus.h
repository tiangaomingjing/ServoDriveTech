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
private:
  Ui::UiStatus *ui;
};

#endif // UISTATUS_H
