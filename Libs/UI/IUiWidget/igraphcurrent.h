#ifndef IGRAPHCURRENT_H
#define IGRAPHCURRENT_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraphwidget.h"
#include "igraph.h"
#include "optface.h"

class IGraphCurrentPrivate;
class IUiWidget;
class AnchorItemHelper;
class WidgetItem;
class ArrowItem;
class QTreeWidgetItem;
class QDoubleSpinBox;

class IUIWIDGETSHARED_EXPORT IGraphCurrent : public IGraphWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphCurrent)
public:

  virtual ~IGraphCurrent();
  virtual void syncTreeDataToUiFace() Q_DECL_OVERRIDE;

protected:
  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
  void createItems() Q_DECL_OVERRIDE;
  virtual void setupDataMappings() = 0;
  void installDoubleSpinBoxEventFilter() Q_DECL_OVERRIDE;
  virtual void setCustomVisitActive(IUiWidget*uiWidget)Q_DECL_OVERRIDE =0;

  void createPIDControllerItem();
  void crtateInputFilterItem();

  void createCurrentFeedbackItem();
  void createSumItem();

  void createArrowItems();

  void setUpItemPosAnchors();

  void adjustPosition();

  void createStartEndItems();
  void createCurrentFeedbackTargetItem();
  void createAnchorItemHelper();
  void createStartTextItem();
  void createEndTextItem();


signals:
protected slots:
  void onFaceCssChanged(const QString &css) Q_DECL_OVERRIDE;

protected:
  IGraphCurrent(IGraphCurrentPrivate&dd, QWidget *parent=0);
};

#endif // IGRAPHCURRENT_H
