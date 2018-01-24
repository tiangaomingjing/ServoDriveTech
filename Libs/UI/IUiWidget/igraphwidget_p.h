#ifndef IGRAPHWIDGET_P_H
#define IGRAPHWIDGET_P_H
#include "iuiwidget_global.h"
class IGraphWidget;
class QGraphicsScene;
class IUIWIDGETSHARED_EXPORT IGraphWidgetPrivate
{
  Q_DECLARE_PUBLIC(IGraphWidget)
public:
  IGraphWidgetPrivate();
  virtual ~IGraphWidgetPrivate();
protected:
  IGraphWidget *q_ptr;
  QGraphicsScene* m_scene;
  QString m_versionName;
};

#endif // IGRAPHWIDGET_P_H

