#ifndef GRAPHBRAKE129_H
#define GRAPHBRAKE129_H

#include <QWidget>
#include "igraphbrake.h"
#include "uibrake_global.h"
#include "optface.h"

namespace Ui {
class GraphBrake129;
}
class GraphBrake129Private;
class QDoubleSpinBox;
class QTreeWidgetItem;

class BrakePaintPrivate:public QWidget
{
  Q_OBJECT
public:
  explicit BrakePaintPrivate(QWidget *parent);
  ~BrakePaintPrivate();
protected:
  void paintEvent(QPaintEvent *event);

private:
};

class UIBRAKESHARED_EXPORT GraphBrake129 : public IGraphBrake
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphBrake129)
public:
  explicit GraphBrake129(QWidget *parent = 0);
  ~GraphBrake129();

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
  void setEditTextStatus(QDoubleSpinBox *box,OptFace::EditTextStatus status);
  void setEditTextStatusDefaultAll();
private:
  Ui::GraphBrake129 *ui;
};

#endif // GRAPHBRAKE129_H
