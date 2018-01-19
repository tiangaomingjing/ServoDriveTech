﻿#ifndef IGRAPHVELOCITY_H
#define IGRAPHVELOCITY_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraphwidget.h"

class IGraphVelocityPrivate;
class IUIWIDGETSHARED_EXPORT IGraphVelocity : public IGraphWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphVelocity)
public:
  explicit IGraphVelocity(QWidget *parent = 0);

signals:

public slots:
protected:
  IGraphVelocity(IGraphVelocityPrivate&d, QWidget *parent=0);
  IGraphVelocityPrivate *d_ptr;
};

#endif // IGRAPHVELOCITY_H
