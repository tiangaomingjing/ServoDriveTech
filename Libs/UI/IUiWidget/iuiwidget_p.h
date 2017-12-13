#ifndef IUIWIDGET_P_H
#define IUIWIDGET_P_H
#include <QObject>
class IUiWidget;
class QStackedWidget;
class QVBoxLayout;
class QTreeWidget;
class SevDevice;
class IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(IUiWidget)
public:
  IUiWidgetPrivate(){}
  virtual ~IUiWidgetPrivate(){}
protected:
  int axisInx;
  quint8 pageInx;
  QStackedWidget *m_uiStackedWidget;
  QVBoxLayout *m_vboxLayout;
  QTreeWidget *m_dataTree;
  SevDevice *m_device;
  IUiWidget *q_ptr;
};

#endif // IUIWIDGET_P_H

