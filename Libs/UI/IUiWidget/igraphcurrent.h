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
  void createStartTextItem();
  void createEndTextItem();

  virtual void createItems();

  virtual void setEditTextStatusDefaultAll();

  virtual void setupDoublespinBoxEventFilter();
  virtual bool eventFilter(QObject *obj, QEvent *event);

  void setEditTextStatus(QDoubleSpinBox *box,OptFace::EditTextStatus status);

signals:

protected slots:
  void onFaceCssChanged(const QString &css);
  void onItemBoxEditTextError(QTreeWidgetItem *item,int status);
  virtual void onDoubleSpinBoxFocusOut();

protected:
  IGraphCurrent(IGraphCurrentPrivate&dd, QWidget *parent=0);
};

#endif // IGRAPHCURRENT_H
