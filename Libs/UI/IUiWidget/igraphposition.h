#ifndef IGRAPHPOSITION_H
#define IGRAPHPOSITION_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraphwidget.h"
#include "igraph.h"

class IGraphPositionPrivate;
class IUiWidget;
class IUIWIDGETSHARED_EXPORT IGraphPosition : public IGraphWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphPosition)
public:
  virtual ~IGraphPosition();
  virtual void syncTreeDataToUiFace() Q_DECL_OVERRIDE;

protected:
  //  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
  //  virtual void setupDataMappings() = 0;//这个放在每一个版本中处理，因为其索引可能不一样
  //  virtual void setCustomVisitActive(IUiWidget*uiWidget)Q_DECL_OVERRIDE =0;
  virtual void createItems() Q_DECL_OVERRIDE;
  virtual void setDoubleSpinBoxConnections() Q_DECL_OVERRIDE;
  virtual void installDoubleSpinBoxEventFilter() Q_DECL_OVERRIDE;
  virtual void adjustPosition() Q_DECL_OVERRIDE;


  virtual void createInputFilterItem();
  virtual void createSumItem0();
  virtual void createPidItem();
  virtual void createSaturationItem();
  virtual void createSumItem1();
  virtual void createVelocityControllerItem();
  virtual void createSumItem2();
  virtual void createCurrentControllerItem();
  virtual void createPositionFeedbackItem();
  virtual void createFFVelocityItem();
  virtual void createFFAccelerationItem();

  virtual void createTargetItems();

  void createStartEndTargetItems();
  void createStartTextItem();
  void createEndTextItem();

  virtual void createArrowItems();
  void createAnchorItemHelper();
  virtual void setUpItemPosAnchors();

signals:

protected:
  IGraphPosition(IGraphPositionPrivate&dd, QWidget *parent=0);
};

#endif // IGRAPHPOSITION_H
