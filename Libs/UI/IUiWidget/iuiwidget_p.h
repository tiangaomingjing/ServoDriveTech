#ifndef IUIWIDGET_P_H
#define IUIWIDGET_P_H
#include <QObject>
class IUiWidget;
class IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(IUiWidget)
public:
  IUiWidgetPrivate(){}
  virtual ~IUiWidgetPrivate(){}
protected:
  quint8 axisInx;
  quint8 pageInx;
  quint8 sdInx;
  IUiWidget *q_ptr;
};

#endif // IUIWIDGET_P_H

