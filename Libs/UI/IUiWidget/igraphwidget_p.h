#ifndef IGRAPHWIDGET_P_H
#define IGRAPHWIDGET_P_H
#include "boxitemmapping.h"
#include "igraphwidget.h"
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
  IGraphWidgetPrivate():
    q_ptr(NULL),
    m_scene(NULL),
    m_versionName(""),
    m_backGroundColor(Qt::black),
    m_arrowColor(Qt::gray),
    m_dev(NULL),
    m_treeWidget(NULL),
    m_uiWidget(NULL),
    m_mapping(new BoxItemMapping)
  {

  }
  virtual ~IGraphWidgetPrivate(){}
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

