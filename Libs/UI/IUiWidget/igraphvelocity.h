#ifndef IGRAPHVELOCITY_H
#define IGRAPHVELOCITY_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraphwidget.h"
#include "igraph.h"

class IGraphVelocityPrivate;
class IUiWidget;
class IUIWIDGETSHARED_EXPORT IGraphVelocity : public IGraphWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphVelocity)
public:

  virtual ~IGraphVelocity();

  virtual void syncTreeDataToUiFace() Q_DECL_OVERRIDE;

protected:
//  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
//  virtual void setCustomVisitActive(IUiWidget*uiWidget)Q_DECL_OVERRIDE =0;
//  virtual void setupDataMappings() = 0;//这个放在每一个版本中处理，因为其索引可能不一样

  virtual void createItems() Q_DECL_OVERRIDE;
  virtual void setDoubleSpinBoxConnections() Q_DECL_OVERRIDE;
  virtual void installDoubleSpinBoxEventFilter() Q_DECL_OVERRIDE;
  virtual void adjustPosition() Q_DECL_OVERRIDE;

  virtual void createInputFilterItem();
  virtual void createSumItem();
  virtual void createPidItem();
  virtual void createSaturationItem();
  virtual void createOutputFilterItem();
  virtual void createVelocityFeedbackItem();

  virtual void createTargetItems();

  void createStartEndTargetItems();
  void createStartTextItem();
  void createEndTextItem();

  virtual void createArrowItems();
  virtual void createSaturationConfigItems();
  void createAnchorItemHelper();
  virtual void setUpItemPosAnchors();

protected slots:
  void onSaturationClicked(bool checked);
private :
  void setSaturationConfigVisible(bool enable);

signals:

protected:
  IGraphVelocity(IGraphVelocityPrivate&dd, QWidget *parent=0);

};

#endif // IGRAPHVELOCITY_H
