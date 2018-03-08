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

  void createItems() Q_DECL_OVERRIDE;
  void setDoubleSpinBoxConnections() Q_DECL_OVERRIDE;
  void installDoubleSpinBoxEventFilter() Q_DECL_OVERRIDE;
  void adjustPosition() Q_DECL_OVERRIDE;

signals:

protected:
  IGraphVelocity(IGraphVelocityPrivate&dd, QWidget *parent=0);

};

#endif // IGRAPHVELOCITY_H
