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
    void createItems() Q_DECL_OVERRIDE;
    void setDoubleSpinBoxConnections() Q_DECL_OVERRIDE;
    void installDoubleSpinBoxEventFilter() Q_DECL_OVERRIDE;
    void adjustPosition() Q_DECL_OVERRIDE;

signals:

protected:
  IGraphPosition(IGraphPositionPrivate&dd, QWidget *parent=0);
};

#endif // IGRAPHPOSITION_H
