#ifndef IGRAPHCURRENT_H
#define IGRAPHCURRENT_H

#include <QWidget>
#include "iuiwidget_global.h"
class IGraphCurrentPrivate;
class IUIWIDGETSHARED_EXPORT IGraphCurrent : public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphCurrent)
public:
  explicit IGraphCurrent(QWidget *parent = 0);

signals:

public slots:
protected:
  IGraphCurrent(IGraphCurrentPrivate&d, QWidget *parent=0);
  IGraphCurrentPrivate *d_ptr;
};

#endif // IGRAPHCURRENT_H
