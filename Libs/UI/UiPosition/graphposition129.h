﻿#ifndef GRAPHPOSITION129_H
#define GRAPHPOSITION129_H

#include <QWidget>
#include "uiposition_global.h"
#include "igraphposition.h"

namespace Ui {
class GraphPosition129;
}
class GraphPosition129Private;
class UIPOSITIONSHARED_EXPORT GraphPosition129 : public IGraphPosition
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphPosition129)
public:
  explicit GraphPosition129(QWidget *parent = 0);
  ~GraphPosition129();

private:
  Ui::GraphPosition129 *ui;
};

#endif // GRAPHPOSITION129_H
