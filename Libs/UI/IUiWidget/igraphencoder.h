﻿#ifndef IGRAPHENCODER_H
#define IGRAPHENCODER_H

#include <QWidget>
#include "iuiwidget_global.h"

class IGraphEncoderPrivate;

class IUIWIDGETSHARED_EXPORT IGraphEncoder : public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphEncoder)
public:
  explicit IGraphEncoder(QWidget *parent = 0);

signals:

public slots:
protected:
  IGraphEncoder(IGraphEncoderPrivate&d, QWidget *parent=0);
  IGraphEncoderPrivate *d_ptr;
};

#endif // IGRAPHENCODER_H
