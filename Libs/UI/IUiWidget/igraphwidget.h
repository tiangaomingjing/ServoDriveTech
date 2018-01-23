#ifndef IGRAPHWIDGET_H
#define IGRAPHWIDGET_H

#include <QGraphicsView>
#include "iuiwidget_global.h"

class QGraphicsScene;
class IUIWIDGETSHARED_EXPORT IGraphWidget : public QGraphicsView
{
  Q_OBJECT
public:
  explicit IGraphWidget(QWidget *parent = 0);
  virtual ~IGraphWidget();
signals:

public slots:
protected:
  QGraphicsScene* m_scene;
};

#endif // IGRAPHWIDGET_H
