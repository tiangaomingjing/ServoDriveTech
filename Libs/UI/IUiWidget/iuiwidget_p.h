#ifndef IUIWIDGET_P_H
#define IUIWIDGET_P_H
#include <QObject>
#include "iuiwidget.h"
class IUiWidget;
class QStackedWidget;
class QVBoxLayout;
class QTreeWidget;
class SevDevice;
class QQuickWidget;
class QAction;
class IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(IUiWidget)
public:
  IUiWidgetPrivate(){}
  virtual ~IUiWidgetPrivate(){}
protected:
  UiIndexs m_index;
  QStackedWidget *m_uiStackedWidget;
  QVBoxLayout *m_vboxLayout;
  QTreeWidget *m_dataTree;
  SevDevice *m_device;
  IUiWidget *q_ptr;
  QString m_qmlpath;
//  QQuickWidget *m_qwidget;
  QWidget *m_qwidget;
  QAction *m_actSwitchView;
  QAction *m_actReadRAM;
  QAction *m_actReadFLASH;
};

#endif // IUIWIDGET_P_H

