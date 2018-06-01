#ifndef UIENCODER_H
#define UIENCODER_H

#include "uiencoder_global.h"
#include "iuiwidget.h"

namespace Ui {
class UiEncoder;
}
class QWidget;
class UiEncoderPrivate;
class UIENCODERSHARED_EXPORT UiEncoder:public IUiWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(UiEncoder)
public:
  explicit UiEncoder(QWidget *parent = 0);
  ~UiEncoder();

  bool hasConfigFunc()Q_DECL_OVERRIDE;
  bool hasSaveFunc()Q_DECL_OVERRIDE;

  void accept(QWidget*w) Q_DECL_OVERRIDE;
  void setUiActive(bool actived)Q_DECL_OVERRIDE;

protected:
  void setContextAction() Q_DECL_OVERRIDE;

protected slots:
  void onDspReset() Q_DECL_OVERRIDE;

signals:
  void encActive();
private:
  QStackedWidget *getUiStackedWidget(void)Q_DECL_OVERRIDE;
  QVBoxLayout *getVBoxLayout(void)Q_DECL_OVERRIDE;
  void setDefaultUi()Q_DECL_OVERRIDE;

private:
  Ui::UiEncoder *ui;
};

#endif // UIENCODER_H
