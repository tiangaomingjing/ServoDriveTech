#ifndef GRAPHVELOCITY133_H
#define GRAPHVELOCITY133_H

#include <QWidget>
#include "uivelocity_global.h"
#include "igraphvelocity.h"

class GraphVelocity133Private;

class UIVELOCITYSHARED_EXPORT GraphVelocity133 : public IGraphVelocity
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphVelocity133)
public:
  explicit GraphVelocity133(QWidget *parent = 0);
  ~GraphVelocity133();

protected:
  void setCustomVisitActive(IUiWidget *uiWidget) Q_DECL_OVERRIDE;
  void setUiVersionName() Q_DECL_OVERRIDE;
  void setupDataMappings() Q_DECL_OVERRIDE;
  void createPidItem() Q_DECL_OVERRIDE;
  QPointF pidInitPos() Q_DECL_OVERRIDE;
  void syncTreeDataToUiFace() Q_DECL_OVERRIDE;
  void installDoubleSpinBoxEventFilter() Q_DECL_OVERRIDE;
  void setDoubleSpinBoxConnections() Q_DECL_OVERRIDE;

private slots:
  void onPidComboBoxSWIndexChanged(int index);

private:
  quint16 readNos(const QString &key);

};

#endif // GRAPHVELOCITY133_H
