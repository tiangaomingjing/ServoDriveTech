#ifndef GRAPHPOWER129_H
#define GRAPHPOWER129_H

#include <QWidget>
#include "igraphpower.h"
#include "uipower_global.h"
#include "optface.h"

class QDoubleSpinBox;
class QTreeWidgetItem;

namespace Ui {
class GraphPower129;
}
class GraphPower129Private;

class UIPOWERSHARED_EXPORT GraphPower129 : public IGraphPower
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphPower129)
public:
  explicit GraphPower129(QWidget *parent = 0);
  ~GraphPower129();
   void syncTreeDataToUiFace()Q_DECL_OVERRIDE;

protected:
  void visitActive(IUiWidget *uiWidget)Q_DECL_OVERRIDE;
  void setUiVersionName()Q_DECL_OVERRIDE;
protected:
  bool eventFilter(QObject *obj, QEvent *event);
protected slots:
  void onItemBoxEditTextError(QTreeWidgetItem *item,int status);
  void onFaceCssChanged(const QString &css);
private:
  Ui::GraphPower129 *ui;
private:
  void setEditTextStatus(QDoubleSpinBox *box,OptFace::EditTextStatus status);
  void setEditTextStatusDefaultAll();
};

#endif // GRAPHPOWER129_H
