#ifndef IGRAPHWIDGET_P_H
#define IGRAPHWIDGET_P_H
#include "iuiwidget_global.h"
#include <QColor>
class IGraphWidget;
class QGraphicsScene;
class SevDevice;
class QTreeWidget;
class BoxItemMapping;
class IUiWidget;
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
  QColor m_backGroundColor;
  QColor m_arrowColor;

  SevDevice *m_dev;
  QTreeWidget *m_treeWidget;
  BoxItemMapping*m_mapping;
  IUiWidget *m_uiWidget;
};

#endif // IGRAPHWIDGET_P_H

