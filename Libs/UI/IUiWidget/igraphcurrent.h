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
//  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
//  virtual void setupDataMappings() = 0;//这个放在每一个版本中处理，因为其索引可能不一样
//  virtual void setCustomVisitActive(IUiWidget*uiWidget)Q_DECL_OVERRIDE =0;
  virtual void createItems() Q_DECL_OVERRIDE;
  virtual void installDoubleSpinBoxEventFilter() Q_DECL_OVERRIDE;
  virtual void setDoubleSpinBoxConnections() Q_DECL_OVERRIDE;
  virtual void adjustPosition() Q_DECL_OVERRIDE;


  virtual void createPidControllerItem();
  virtual void createInputFilterItem();

  virtual void createCurrentFeedbackItem();
  virtual void createSumItem();

  virtual void createArrowItems();

  void createStartEndTargetItems();
  void createCurrentFeedbackTargetItem();

  void createStartTextItem();
  void createEndTextItem();

  void createAnchorItemHelper();
  virtual void setUpItemPosAnchors();


signals:

protected:
  IGraphCurrent(IGraphCurrentPrivate&dd, QWidget *parent=0);
};

#endif // IGRAPHCURRENT_H
