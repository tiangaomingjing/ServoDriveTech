#ifndef IGRAPHCURRENT_H
#define IGRAPHCURRENT_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraphwidget.h"
#include "igraph.h"

class IGraphCurrentPrivate;
class IUiWidget;
class AnchorItemHelper;
class WidgetItem;
class ArrowItem;

class IUIWIDGETSHARED_EXPORT IGraphCurrent : public IGraphWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphCurrent)
public:
  explicit IGraphCurrent(QWidget *parent = 0);
  virtual ~IGraphCurrent();

protected:
  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
  virtual void visitActive(IUiWidget*uiWidget)Q_DECL_OVERRIDE =0;

  virtual void createPIDControllerItem();
  virtual void crtateInputFilterItem();

  virtual void createCurrentFeedbackItem();
  virtual void createSumItem();

  virtual void createArrowItems();

  virtual void setUpItemPosAnchors();

  virtual void adjustPosition();

  void createStartEndItems();
  void createCurrentFeedbackTarget();
  void createAnchorItemHelper();

  virtual void createItems();

signals:

public slots:
protected:
  IGraphCurrent(IGraphCurrentPrivate&dd, QWidget *parent=0);
};

#endif // IGRAPHCURRENT_H
