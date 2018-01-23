#ifndef IGRAPHENCODER_H
#define IGRAPHENCODER_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraph.h"

class IGraphEncoderPrivate;
class IUiWidget;

class IUIWIDGETSHARED_EXPORT IGraphEncoder : public IGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphEncoder)
public:
  explicit IGraphEncoder(QWidget *parent = 0);
  virtual ~IGraphEncoder();
  virtual void visit(IUiWidget*ui)Q_DECL_OVERRIDE =0;

signals:

public slots:
protected:
  IGraphEncoder(IGraphEncoderPrivate&d, QWidget *parent=0);
};

#endif // IGRAPHENCODER_H
