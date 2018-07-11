#ifndef GRAPHSTATUS129_H
#define GRAPHSTATUS129_H

#include <QWidget>
#include "igraphstatus.h"
#include "uistatus_global.h"

namespace Ui {
class GraphStatus129;
}
class GraphStatus129Private;
class UISTATUSSHARED_EXPORT GraphStatus129 : public IGraphStatus
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GraphStatus129)
public:
  explicit GraphStatus129(QWidget *parent = 0);
  ~GraphStatus129();

protected:
  void setUiVersionName() Q_DECL_OVERRIDE;
  void setupDataMappings() Q_DECL_OVERRIDE;
  void setDeviceStatusIconByCss(const QString &css) Q_DECL_OVERRIDE;
  QWidget *alarmBackgroundWidget() Q_DECL_OVERRIDE;
  void addLedErrorToUi() Q_DECL_OVERRIDE;
  quint32 alarmCode() Q_DECL_OVERRIDE;
  bool hasError() Q_DECL_OVERRIDE;
  void updateUiLabelText() Q_DECL_OVERRIDE;

private slots:
  void onBtnClearAlarmClicked();

private:
  Ui::GraphStatus129 *ui;
};

#endif // GRAPHSTATUS129_H
