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

  void syncTreeDataToUiFace()Q_DECL_OVERRIDE;

protected:
  void setCustomVisitActive(IUiWidget *uiWidget)Q_DECL_OVERRIDE;
  void setUiVersionName()Q_DECL_OVERRIDE;
  void setupDataMappings() Q_DECL_OVERRIDE;


  void onUpdateTimeOut() Q_DECL_OVERRIDE;
  quint32 getLineNumber()Q_DECL_OVERRIDE;
  void createSupportEncoderItem() Q_DECL_OVERRIDE;

private slots:
  void onBtnEncConfigClicked(bool checked);//打开编码器配置界面
  void onBtnEncConfigSaveClicked();//保存编码器配置
  void onRadioBtnClicked();
  void onBtnSearchPhaseClicked();

  void onEncConfigListWidgetRowChanged(int curRow);

  void onEncActive();

  void onBtnClearEcnAlarmClicked();


private:
  void initDial(QwtDial *dial);
  void setEncConfigUiEnable(bool en);
  void setEncErrorUiEnable(bool en);

  void updateEncConfigUiByCurrentConfigItem();

  void showEncoderError(quint16 lost,quint16 encinfo);
  void initCurEncConfigItem();

private:
  Ui::GraphEncoder129 *ui;
};

#endif // GRAPHENCODER129_H
