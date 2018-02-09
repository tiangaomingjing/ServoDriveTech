#ifndef GRAPHENCODER129_H
#define GRAPHENCODER129_H

#include <QWidget>
#include "igraphencoder.h"
#include "uiencoder_global.h"

namespace Ui {
class GraphEncoder129;
}
class GraphEncoder129Private;
class QwtDial;

class UIENCODERSHARED_EXPORT GraphEncoder129 : public IGraphEncoder
{
  Q_OBJECT

  Q_DECLARE_PRIVATE(GraphEncoder129)
public:
  explicit GraphEncoder129(QWidget *parent = 0);
  ~GraphEncoder129();

protected:
  void visitActive(IUiWidget *uiWidget)Q_DECL_OVERRIDE;
  void setUiVersionName()Q_DECL_OVERRIDE;
  void syncTreeDataToUiFace()Q_DECL_OVERRIDE;

private slots:
  void onBtnEncConfigClicked(bool checked);
  void onBtnEncConfigSaveClicked();
  void onRadioBtnClicked();
  void onBtnSearchPhaseClicked();

private:
  void initDial(QwtDial *dial);
  void setEncConfigUiEnable(bool en);
  void setEncErrorUiEnable(bool en);

  void updateEncConfigUiByCurrentConfigItem();

private:
  Ui::GraphEncoder129 *ui;
};

#endif // GRAPHENCODER129_H
