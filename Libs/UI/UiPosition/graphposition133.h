#ifndef GRAPHPOSITION133_H
#define GRAPHPOSITION133_H

#include <QWidget>
#include "uiposition_global.h"
#include "igraphposition.h"

class GraphPosition133Private;
class UIPOSITIONSHARED_EXPORT GraphPosition133 : public IGraphPosition
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphPosition133)
public:
  explicit GraphPosition133(QWidget *parent = 0);
  ~GraphPosition133();
protected:
  void setCustomVisitActive(IUiWidget *uiWidget) Q_DECL_OVERRIDE;
  void setupDataMappings() Q_DECL_OVERRIDE;
  void setUiVersionName() Q_DECL_OVERRIDE;
  void createPidItem() Q_DECL_OVERRIDE;
  void createItems() Q_DECL_OVERRIDE;
  void createArrowItems() Q_DECL_OVERRIDE;
  void setUpItemPosAnchors() Q_DECL_OVERRIDE;
  void syncTreeDataToUiFace() Q_DECL_OVERRIDE;
  void installDoubleSpinBoxEventFilter() Q_DECL_OVERRIDE;
  void setDoubleSpinBoxConnections() Q_DECL_OVERRIDE;
  QPointF pidInitPos() Q_DECL_OVERRIDE;
  bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
  void setEditTextStatusDefaultAll() Q_DECL_OVERRIDE;

protected slots:
  void onItemBoxEditTextError(QTreeWidgetItem *item, int status) Q_DECL_OVERRIDE;
  void onDoubleSpinBoxFocusOut() Q_DECL_OVERRIDE;
  void onUIFItemClicked();
  void onFilterConfigClicked();
  void onFilterSaveClicked();
  void onRadioBtnClicked();
  void onPidComboBoxKpSWIndexChanged(int index);
  void onListWidgetSelectIndexChanged(int index);
  void onNlcDirChanged(int dir);
  void onNlcKuChanged(int index);
  void onNlcSWChanged(bool isOn);
  void onBtnAutoStartClicked(bool checked);
  void onAutoTurningProgressValueChanged(int value);

private:
  void createPosDirItem();
  quint16 readNos(const QString &key);
  void setControllerUi(int index);

};

#endif // GRAPHPOSITION133_H
